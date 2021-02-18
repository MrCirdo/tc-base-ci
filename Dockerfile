FROM archlinux:latest


RUN patched_glibc=glibc-linux4-2.33-4-x86_64.pkg.tar.zst && \
curl -LO "https://repo.archlinuxcn.org/x86_64/$patched_glibc" && \
bsdtar -C / -xvf "$patched_glibc"

RUN pacman -Syu --noconfirm clang gtest autoconf automake autoconf-archive boost gcc libtool zsh dash bash flex bison m4 make

RUN bsdtar -C / -xvf "$patched_glibc"

COPY cri-mirror /cri-mirror
RUN cat /cri-mirror >> /etc/pacman.conf

COPY clang-format /.clang-format

RUN mkdir /project

COPY . /project

WORKDIR /project

ENV LC_ALL=C
RUN echo $SHELL
ENV CONFIG_SHELL=/bin/bash
ENV M4=/bin/m4
RUN aclocal
RUN autoreconf -vif

# && ./configure && make

#ENV M4=/usr/bin/m4
#RUN CONFIG_SHELL=/usr/bin/zsh zsh ./bootstrap
#RUN zsh /usr/bin/autoconf || zsh --version
#RUN zsh /usr/bin/autoconf --version || echo bad; echo $CONFIG_SHELL; CONFIG_SHELL=/usr/bin/zsh /usr/bin/autoconf
#RUN ./configure
#RUN make SHELL=
