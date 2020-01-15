FROM gcc:latest

COPY . /usr/src/myapp
WORKDIR /usr/src/myapp

RUN make all

EXPOSE 8080

CMD ["./main"]