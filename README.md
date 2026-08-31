# lipu CE

**lipu CE** is a [toki pona](https://en.wikipedia.org/wiki/Toki_Pona) dictionary for the TI-84 Plus CE calculator. *It is currently early in development!*

## Building

The repo uses python scripts to build the dictionary database and sitelen pona glyphs. To build, `python3` must be in PATH.

```bash
pip3 install -r requirements.txt
make gfx && make
```

##  License

This project is licensed under the MIT License.
Dictionary data is sourced from [lipu-linku/sona](https://github.com/lipu-linku/sona) and licensed under [CC-BY-SA-4.0 license](https://github.com/lipu-linku/sona/blob/main/LICENSE).
Fairfax font is licensed under SIL Open Font License 1.1.
