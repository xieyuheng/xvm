# XVM

XVM is an extensible 64-bit stack virtual machine with tagged value.

## Usage

Dependencies:

- `libx11`:
  - debian: `sudo apt install libx11-dev`
  - ubuntu: `sudo apt install libx11-dev`

Compile:

```
git clone https://github.com/cicada-lang/xvm
cd xvm
make -j
make test
```

The compiled `bin/x` is the command-line program.

```sh
x run         # run a script
x version     # print version
x help        # print help
```

## Development

```sh
make all      # compile src/ files to lib/ and bin/
make run      # compile and run the command-line program
make test     # compile and run test
make clean    # clean up compiled files
```

## References

**Inspirations**:

- [uxn](https://100r.co/site/uxn.html)

**Books**:

- [Scalable C](https://github.com/booksbyus/scalable-c)

## License

[GPLv3](LICENSE)
