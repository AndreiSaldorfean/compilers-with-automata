all: clean
	cmake -S . -B build -G "Unix Makefiles"
	@if [ -f ./compile_commands.json ]; then \
		echo 'removed compile_commands.json'; \
		rm -f compile_commands.json; \
	else \
		echo "compile_commands.json not found"; \
	fi
	@mv build/compile_commands.json .

clean:
	@rm -rf build/*

cp:
	@cd build && make -j12

r:
	@cd build && ./main

cpr: cp r

