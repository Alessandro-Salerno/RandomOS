WORKING_DIRECTORY    = "$(shell dirname $(realpath $(firstword $(MAKEFILE_LIST))))"

ASSETS_DIR           = Assets
OUTPUT_DIR           = Output

MAKE                 = make
GIT                  = git
DOCKER               = docker
DOCKER_INPUT         = Docker
DOCKER_OUTPUT        = randomos-buildenv
DOCKER_PLATFORM	    = linux/x86_64
DOCKER_PLATFORM_ARGS = --platform $(DOCKER_PLATFORM)
DOCKER_GLOBAL_ARGS   = --rm -it -v $(WORKING_DIRECTORY):/root/env


setup:
	@ echo !=== PREPARING COMPONENTS
	$(MAKE) -C RandomOS limine

download:
	@ echo !=== DOWNLOADING DOCKER DEPENDENCIES
	$(DOCKER) build $(DOCKER_INPUT) -t $(DOCKER_OUTPUT)

enter:
	@ echo !=== ENTERING ENVIRONMENT
	$(DOCKER) run $(DOCKER_GLOBAL_ARGS) $(DOCKER_OUTPUT)
 
 clean:
	@ echo !=== CLEANING
	@ $(MAKE) -C RandomOS distclean
