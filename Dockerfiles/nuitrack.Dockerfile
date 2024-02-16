FROM ubuntu:22.04 as arm64

COPY nuitrack-linux-arm64.deb /
RUN dpkg -i nuitrack-linux-arm64.deb && rm nuitrack-linux-arm64.deb

FROM ubuntu:22.04 as amd64

COPY nuitrack-ubuntu-amd64.deb /
RUN dpkg -i nuitrack-ubuntu-amd64.deb && rm nuitrack-ubuntu-amd64.deb

FROM $TARGETARCH

ARG VERSION

LABEL author="3DiVi Inc" \
      description="Official Nuitrack image" \
      website="https://nuitrack.com/" \
      version=$VERSION

RUN apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y \
    libgtk2.0-0 libgomp1 ca-certificates usbutils \
    && rm -rf /var/lib/apt/lists/* && rm -rf /var/cache/apt
    
ENTRYPOINT ["nuitrack_device_api_sample"]
