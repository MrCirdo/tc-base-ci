FROM archlinux:latest


RUN patched_glibc=glibc-linux4-2.33-4-x86_64.pkg.tar.zst && \
curl -LO "https://repo.archlinuxcn.org/x86_64/$patched_glibc" && \
bsdtar -C / -xvf "$patched_glibc"

RUN pacman -Syu --noconfirm clang gtest autoconf automake autoconf-archive boost gcc libtool bash flex bison

RUN bsdtar -C / -xvf "$patched_glibc"

COPY cri-mirror /cri-mirror
RUN cat /cri-mirror >> /etc/pacman.conf

COPY clang-format /.clang-format

RUN mkdir /project

COPY . /project

WORKDIR /project

RUN ls
RUN /bin/sh /usr/bin/autoconf || /bin/sh --version
RUN /bin/sh /usr/bin/autoconf --version
RUN /bin/sh ./bootstrap
RUN /bin/sh ./configure
RUN make