CC = gcc

QCFLAGS := -std=gnu99  
QCFLAGS += -fopenmp  # TODO Is this needed?
QCFLAGS += -fPIC      
QCFLAGS += -O3  
QCFLAGS += -W 
QCFLAGS += -Waggregate-return 
QCFLAGS += -Wall 
QCFLAGS += -Wcast-align 
QCFLAGS += -Wcast-qual 
QCFLAGS += -Wmissing-prototypes 
QCFLAGS += -Wnested-externs 
# ??? QCFLAGS += -Wno-pedantic 
# ??? QCFLAGS += -Wno-unused-label  
QCFLAGS += -Wmissing-declarations 
QCFLAGS += -Wmissing-prototypes 
QCFLAGS += -Wnested-externs  
QCFLAGS += -Wold-style-definition 
QCFLAGS += -Wpointer-arith  
QCFLAGS += -Wredundant-decls 
QCFLAGS += -Wshadow 
QCFLAGS += -Wstrict-prototypes 
QCFLAGS += -Wsuggest-attribute=noreturn
QCFLAGS += -Wunused-variable  
QCFLAGS += -Wunused-parameter 
QCFLAGS += -Wwrite-strings 

INCS := -I./inc/ 

all: librs_hmap_core.so 

SRCS :=	./src/calc_new_size.c  
SRCS +=	./src/fasthash.c  
SRCS +=	./src/mk_hmap_key.c  
SRCS +=	./src/murmurhash.c  
SRCS +=	./src/prime_geq.c  
SRCS +=	./src/set_probe_loc.c  

SRCS +=	./src/get_time_usec.c  # TODO should come from librsutils.so
SRCS +=	./src/mk_dir_file_name.c  # TODO should come from librsutils.so
SRCS +=	./src/rdtsc.c  # TODO should come from librsutils.so
SRCS +=	./src/rs_mmap.c # TODO should come from librsutils.so  
SRCS +=	./src/spooky_hash.c  # TODO should come from librsutils.so

OBJS = $(SRCS:.c=.o)

.c.o : ${INCFILES}
	$(CC) -c -o $@ $< ${QCFLAGS} $(INCS) 

INCFILES := ./inc/calc_new_size.h
INCFILES += ./inc/mk_hmap_key.h 
INCFILES += ./inc/prime_geq.h
# TODO Complete INCFILES

# Following to avoid warnings in other people's code 
./src/fasthash.o   : QCFLAGS += -Wno-implicit-fallthrough
./src/spooky_hash.o : QCFLAGS += -Wno-implicit-fallthrough -Wno-cast-qual
#---------------
./inc/get_time_usec.h: ./src/get_time_usec.c
	lua ../utils/cli_extract_func_decl.lua src/get_time_usec.c ./inc/
./inc/mk_dir_file_name.h: ./src/mk_dir_file_name.c
	lua ../utils/cli_extract_func_decl.lua src/mk_dir_file_name.c ./inc/
./inc/rdtsc.h: ./src/rdtsc.c
	lua ../utils/cli_extract_func_decl.lua src/rdtsc.c ./inc/
./inc/rs_mmap.h: ./src/rs_mmap.c
	lua ../utils/cli_extract_func_decl.lua src/rs_mmap.c ./inc/

./inc/calc_new_size.h: ./src/calc_new_size.c
	lua ../utils/cli_extract_func_decl.lua src/calc_new_size.c ./inc/
	lua ../utils/cli_extract_func_decl.lua src/rs_mmap.c ./inc/
./inc/mk_hmap_key.h: ./src/mk_hmap_key.c
	lua ../utils/cli_extract_func_decl.lua src/mk_hmap_key.c ./inc/
./inc/prime_geq.h: ./src/prime_geq.c
	lua ../utils/cli_extract_func_decl.lua src/prime_geq.c ./inc/
./inc/set_probe_loc.h: ./src/set_probe_loc.c
	lua ../utils/cli_extract_func_decl.lua src/set_probe_loc.c ./inc/


./src/calc_new_size.o: ./inc/prime_geq.h ./inc/calc_new_size.h
./src/mk_hmap_key.o: ./inc/mk_hmap_key.h ./inc/rdtsc.h
./src/set_probe_loc.o: ./inc/set_probe_loc.h


./src/get_time_usec.o: ./inc/prime_geq.h ./inc/get_time_usec.h
./src/mk_dir_file_name.o: ./inc/mk_dir_file_name.h ./inc/rdtsc.h
./src/rdtsc.o: ./inc/rdtsc.h
./src/rs_mmap.o: ./inc/rs_mmap.h

librs_hmap_core.so: ${OBJS} 
	gcc  ${OBJS} -shared -lm -o librs_hmap_core.so  -ldl 

clean:
	rm -f *.o *.so src/*.o  $(INCFILES)
