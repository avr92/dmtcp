# To demonstrate, do:  make check    [Checkpoints every 5 seconds]

# The name will be the same as the current directory name.
NAME=${shell basename $$PWD}

# By default, your resulting plugin library will have this name.
LIBNAME=libdmtcp_plugin-to-announce-events

# As you add new files to your plugin library, add the object file names here.
LIBOBJS = plugin-to-announce-events.o

# Modify if your DMTCP_ROOT is located elsewhere.
ifndef DMTCP_ROOT
  DMTCP_ROOT=/home/swapnil/dmtcp/
endif
DMTCP_INCLUDE=${DMTCP_ROOT}/include

override CFLAGS += -fPIC -I${DMTCP_INCLUDE}
override CXXFLAGS += -fPIC -I${DMTCP_INCLUDE}
LINK = ${CC}

DEMO_PORT=7779

default: ${LIBNAME}.so applic

# NOTE:  ${CFLAGS} expands to invoke '-fPIC -I${DMTCP_INCLUDE}'
#        This is required for use with DMTCP.
applic: applic.c
	${CC} ${CFLAGS} -o $@ $< -ldl -Werror

check: ${LIBNAME}.so applic
	@ echo "============ TESTING ./applic WITH DMTCP ================="
	${DMTCP_ROOT}/bin/dmtcp_launch --quiet --coord-port ${DEMO_PORT} \
	  --with-plugin $$PWD/${LIBNAME}.so ./applic
	@ echo ""
	@ sleep 5

res:
	@ echo "===== RESTARTING USING checkpoint file ============="
	dmtcp_restart -j ckpt*.dmtcp
	@ echo ""

${LIBNAME}.so: ${LIBOBJS}
	${LINK} -shared -fPIC -o $@ $^

.c.o:
	${CC} ${CFLAGS} -c -o $@ $<
.cpp.o:
	${CXX} ${CXXFLAGS} -c -o $@ $<

tidy:
	rm -f *~ .*.swp dmtcp_restart_script*.sh ckpt_*.dmtcp

clean: tidy
	rm -f ${LIBOBJS} ${LIBNAME}.so applic

distclean: clean
	rm -f ${LIBNAME}.so *~ .*.swp dmtcp_restart_script*.sh ckpt_*.dmtcp

dist: distclean
	dir=`basename $$PWD`; cd ..; \
	  tar czvf $$dir.tar.gz --exclude-vcs ./$$dir
	dir=`basename $$PWD`; ls -l ../$$dir.tar.gz

.PHONY: default clean dist distclean
