all: magma lesha module

magma:
	cd magma-cipher; \
	cargo build --release
	cp magma-cipher/target/release/libmagma_cipher.so lib/

lesha:
	g++ -fPIC -shared Lesha_cipher/coder.cpp -o lib/libaes.so

module:
	g++ -fPIC -shared encryption_by_modular_arithmetic/main.cpp -o lib/libmodule.so
