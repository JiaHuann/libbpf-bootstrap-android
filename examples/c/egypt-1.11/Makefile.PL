use strict;
use ExtUtils::MakeMaker;
WriteMakefile(NAME => 'egypt',
              AUTHOR => 'Andreas Gustafsson',
              VERSION_FROM => 'egypt',
              ABSTRACT => 'A tool for creating call graphs of C programs',
              EXE_FILES => [ 'egypt' ]
             );
