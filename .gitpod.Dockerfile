# You can find the new timestamped tags here: https://hub.docker.com/r/gitpod/workspace-base/tags
#FROM gitpod/workspace-base:2022-05-08-14-31-53
#FROM gitpod/workspace-mysql:2023-11-04-12-07-48
FROM docker pull debian:testing-slim

# Install custom tools, runtime, etc.
# base image only got `apt` as the package manager
# install-packages is a wrapper for `apt` that helps skip a few commands in the docker env.
