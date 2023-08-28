//用户态程序
#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <time.h>
#include <sys/resource.h>
#include "bpf/libbpf.h"
//和内核态共享数据结构
#include "common.h"
//经过bpftool处理的内核态程序头文件（内核态"嵌入"到用户态）
#include "myringbuffer.skel.h"



int libbpf_print_fn(enum libbpf_print_level level, const char *format, va_list args)
{
	/* Ignore debug-level libbpf logs */
	if (level > LIBBPF_INFO)
		return 0;
	return vfprintf(stderr, format, args);
}

//取消内核内存限制
void bump_memlock_rlimit(void)
{
	struct rlimit rlim_new = { .rlim_cur = RLIM_INFINITY, .rlim_max = RLIM_INFINITY};
	//更新+错误处理
	if (setrlimit(RLIMIT_MEMLOCK, &rlim_new)) {
		fprintf(stderr, "Failed to relimit OS source");
		exit(1);
	}
}

//处理CTRL-C
static volatile bool exiting = false;

static void sig_handler(int sig)
{
	exiting = true;
}

//回调处理函数
int ringbuf_event_handler(void *ctx, void *data, size_t data_sz)
{
	const struct mydata_t * md = data;
	printf("[ringbuf-handler] nr_running->%d cpu->%d \n", md->__nr_running, md->__cpu);
	return 0;
}

//主逻辑
int main(int argc, char **argv)
{
	struct ring_buffer *rb = NULL;
	//通过${apps}.skel.h操作控制交互内核态程序
	struct myringbuffer_bpf *skel;
    int err;


	//logs
	libbpf_set_print(libbpf_print_fn);
	//os settings
	bump_memlock_rlimit();
	//Clean handling
	signal(SIGINT, sig_handler);
	signal(SIGTERM, sig_handler);

//---------------------------------------------------------------
	//加载，验证ebpf内核态程序
	skel = myringbuffer_bpf__open_and_load();
	if (!skel) {
		fprintf(stderr, "failed to open and verify BPF skeleton");
		return -1;
	}

	//挂载
	err = myringbuffer_bpf__attach(skel);
	if (err) {
		fprintf(stderr, "Failed to attach BPF skeleton");
		goto cleanup; //良好习惯清理资源
	}

	/*-----------------------ringbuffer操作部分--------------------*/
	rb = ring_buffer__new(bpf_map__fd(skel->maps.rb), ringbuf_event_handler, NULL, NULL);
	if (!rb) {
		err = -1;
		fprintf(stderr, "Failed to create ring buffer\n");
		goto cleanup;
	}
	

	while (!exiting) {
		err = ring_buffer__poll(rb, -1);
		if (err == -EINTR) {
			err = 0;
			break;
		}
		if (err < 0) {
			printf("Error polling ring buffer: %d\n", err);
			break;
		}
	}

cleanup:
	ring_buffer__free(rb);
	myringbuffer_bpf__destroy(skel);

	return err < 0 ? -err : 0;
}