# Simple C++ API with Docker

Live version [here](https://api-hash-66s4eov4nq-ew.a.run.app/hash/1337). Deployed via Google Cloud Run using a simple Dockerfile.


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

- `make all` and `./main`
- `docker build -t cpp-api .` and `docker run -p 8080:8080 cpp-api`

Then make requests to [localhost:8080/hash/1337](http://localhost:8080/hash/1337).
