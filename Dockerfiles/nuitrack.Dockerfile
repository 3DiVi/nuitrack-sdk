FROM ubuntu:22.04

ARG VERSION

LABEL author="3DiVi Inc" \
      description="Official Nuitrack image" \
      website="https://nuitrack.com/" \
      version=$VERSION

RUN apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y \
    libgtk2.0-0 libgomp1 ca-certificates usbutils \
    && rm -rf /var/lib/apt/lists/* && rm -rf /var/cache/apt

COPY nuitrack-ubuntu-amd64.deb /

RUN dpkg -i nuitrack-ubuntu-amd64.deb && rm nuitrack-ubuntu-amd64.deb

ENTRYPOINT ["nuitrack_device_api_sample"]
