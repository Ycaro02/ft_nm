FROM ubuntu:22.04

# Install dependencies
RUN apt update && apt install -y make gcc git vim zsh curl valgrind

# Get oh-my-zsh for a better terminal experience
RUN apt update && apt install -y make gcc git vim zsh curl valgrind libc6-dev-i386 wget

# Create a home dir for the app
RUN mkdir -p /home/nfour/app

# Set the workdir
WORKDIR /home/nfour/app

# Copy the app to the container
COPY . .

# Clone the tester
RUN git clone https://github.com/Ycaro02/ft_nmTester.git

# Build the image with:
	# docker build -t ft_nm .
# Run the image with zsh as the entrypoint with:
	# docker run -it ft_nm zsh

# Run the image with all verbose test (without valgrind)
	# docker run -it ft_nm ./ft_nmTester/call_tester.sh 0 1 1
