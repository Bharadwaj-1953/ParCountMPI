# Use Ubuntu 20.04 as the base image
FROM ubuntu:20.04

# Set environment variable to prevent interactive prompts
ENV DEBIAN_FRONTEND=noninteractive
ENV USERNAME=mpi
ENV PASSWORD=mpi

RUN apt-get update && apt-get install -y \
    build-essential \
    wget \
    curl \
    python3 \
    python3-pip \
    openssh-client \
    openssh-server \
    openmpi-bin \
    libopenmpi-dev

RUN pip3 install mpi4py

RUN useradd -m $USERNAME && \
    usermod -s /bin/bash $USERNAME && \
    echo "$USERNAME:$PASSWORD" | chpasswd

COPY .ssh /home/$USERNAME/.ssh

RUN chmod 600 /home/$USERNAME/.ssh/authorized_keys && \
    chown -R $USERNAME:$USERNAME /home/$USERNAME/.ssh && \
    echo "Host *" > /home/$USERNAME/.ssh/config && \
    echo "   StrictHostKeyChecking no" >> /home/$USERNAME/.ssh/config 
EXPOSE 22

RUN mkdir -p /run/sshd && chmod 755 /run/sshd
RUN echo "export PATH=/usr/lib64/openmpi/bin:\$PATH" >> /home/$USERNAME/.bashrc
RUN echo "export LD_LIBRARY_PATH=/usr/lib64/openmpi/lib:\$LD_LIBRARY_PATH" >> /home/$USERNAME/.bashrc
ENTRYPOINT ["/usr/sbin/sshd", "-D"]
