# minish




minish:	minish.o ejecutar.o externo.o linea2argv.o builtin/builtin_cd.o builtin/builtin_dir.o builtin/builtin_exit.o builtin/builtin_getenv.o builtin/builtin_gid.o builtin/builtin_help.o builtin/builtin_history.o builtin/builtin_pid.o builtin/builtin_setenv.o builtin/builtin_status.o builtin/builtin_uid.o builtin/builtin_unsetenv.o

minish.o:	minish.h
ejecutar.o:	minish.h
externo.o:	minish.h

builtin/builtin_cd.o: minish.h
builtin/builtin_dir.o: minish.h
builtin/builtin_exit.o: minish.h
builtin/builtin_getenv.o: minish.h
builtin/builtin_gid.o: minish.h
builtin/builtin_help.o: minish.h
builtin/builtin_history.o: minish.h
builtin/builtin_pid.o: minish.h
builtin/builtin_setenv.o: minish.h
builtin/builtin_status.o: minish.h
builtin/builtin_uid.o: minish.h
builtin/builtin_unsetenv.o: minish.h