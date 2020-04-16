FROM ubuntu:12.04

RUN sed -i -e "s/archive.ubuntu.com/old-releases.ubuntu.com/g" /etc/apt/sources.list

RUN apt-get update
#RUN apt-get upgrade -y 
RUN apt-get -y install build-essential python diffstat texinfo\
  texi2html cvs subversion wget gawk help2man xmlto curl \
  zip subversion git-core gcc-multilib

RUN ln -sf /bin/bash /bin/sh

RUN useradd -ms /bin/bash squeezeos
WORKDIR /home/squeezeos

CMD ["su", "-", "squeezeos", "-c", "/bin/bash"]