WORKSPACE = build

.PHONY: build clear workspase

build: pqxx workspase
	cd ${WORKSPACE} && cmake .. && cmake --build . && cd .. && make clear

workspase: clear
	mkdir ${WORKSPACE}

pqxx: 
	sudo usermod -a -G sudo gitlab-runner && sudo apt install libpqxx-dev

clear:
	rm -rf ${WORKSPACE}