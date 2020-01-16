# Simple C++ API with Docker

Live version [here](https://cpp-api.tarasyarema.com/hash/1337). Deployed via Google Cloud Run using a simple Dockerfile.

It uses [this](https://github.com/yhirose/cpp-httplib) header only library.

**Disclamer**: There are no error handlers, this is only a proof of concept.

## Endpoints

`GET /hash/<number>`

and it returns a simple hash of the given number

```
{
  "hash": <number_hash>
}
```

## Run

- `make all` (`make fast` for developing) and `./main`
- `docker build -t cpp-api .` and `docker run -p 8080:8080 cpp-api`

Then you can make requests to [localhost:8080/hash/1337](http://localhost:8080/hash/1337).
