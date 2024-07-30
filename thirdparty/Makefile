# Llama a los make de subdirectorios

.PHONY: all clean cleanall

all: cleanall
	$(MAKE) -C GLAD
	$(MAKE) -C GLAD clean
	$(MAKE) -C stb
	$(MAKE) -C stb clean
	$(MAKE) -C ImGui
	$(MAKE) -C ImGui clean

clean:
	$(MAKE) -C GLAD clean
	$(MAKE) -C stb clean
	$(MAKE) -C ImGui clean

cleanall:
	$(MAKE) -C GLAD cleanall
	$(MAKE) -C stb cleanall
	$(MAKE) -C ImGui cleanall
