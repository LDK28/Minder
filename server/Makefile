WORKSPACE = build

.PHONY: build clear workspase

build: workspase
	cd ${WORKSPACE} && cmake .. && cmake --build . && cd .. && make clear

workspase: clear
	mkdir ${WORKSPACE}

clear:
	rm -rf ${WORKSPACE}