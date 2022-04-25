FROM gcc:latest
COPY . /usr/src/worker
WORKDIR /usr/src/worker
RUN g++ -o worker worker.cpp
CMD ["./worker"]