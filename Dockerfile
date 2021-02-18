FROM archlinux:latest


RUN patched_glibc=glibc-linux4-2.33-4-x86_64.pkg.tar.zst && \
curl -LO "https://repo.archlinuxcn.org/x86_64/$patched_glibc" && \
bsdtar -C / -xvf "$patched_glibc"

RUN pacman -Syu --noconfirm clang gtest autoconf automake autoconf-archive boost gcc libtool zsh flex bison m4 make

RUN bsdtar -C / -xvf "$patched_glibc"

COPY cri-mirror /cri-mirror
RUN cat /cri-mirror >> /etc/pacman.conf

COPY clang-format /.clang-format

RUN mkdir /project

COPY . /project

WORKDIR /project
RUN ls
RUN echo $PATH
RUN echo M4: $M4
ENV M4=/usr/bin/m4
ENV CONFIG_SHELL=/usr/bin/zsh
RUN zsh ./bootstrap
RUN zsh ./configure
RUN make
