check-local:
if FUNCTIONAL
	dune runtest
else
	@echo -ne '\x1B[91m'
	@echo '┌────────────────────────────────────┐'
	@echo '│                                    │'
	@echo '│          dune is required          │'
	@echo '│                                    │'
	@echo '│    you can install it with opam    │'
	@echo '│    then run `eval $$(opam env)`     │'
	@echo '│                                    │'
	@echo '└────────────────────────────────────┘'
	@echo -ne '\x1B[0m'
endif

mostlyclean-local:
if FUNCTIONAL
	dune clean
endif
