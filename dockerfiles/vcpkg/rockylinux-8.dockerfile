ARG VCPKG_REF=latest
FROM hpccsystems/platform-build-base-rockylinux-8:$VCPKG_REF

ENTRYPOINT ["/bin/bash", "--login", "-c"]

CMD ["/bin/bash"]
