.PHONY: clean All

All:
	@echo "----------Building project:[ Flare - Debug ]----------"
	@cd "Flare" && "$(MAKE)" -f  "Flare.mk"
clean:
	@echo "----------Cleaning project:[ Flare - Debug ]----------"
	@cd "Flare" && "$(MAKE)" -f  "Flare.mk" clean
