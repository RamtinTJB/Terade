# Terade
A terminal based cryptocurrency trading simulator. 

## Motivation
For my honor's project for the *CISC 187: Data Structures in C++* I chose to create a cryptocurrency trading simulator, as a way to integrate my interest in the cryptocurrencies and the knowledge I acquired in the class about data structures. 

## Screenshots

<p align="center">
	<img width="460" height="300" src="/img/Screenshot1.png">
</p>

<p align="center">
	<img width="460" height="300" src="/img/Screenshot2.png">
</p>

<p align="center">
	<img width="460" height="300" src="/img/Screenshot3.png">
</p>

## Libraries/APIs Used

* **[CoinGecko API](https://www.coingecko.com/en/api)**

All the necessary data for the simulation were downloaded from the CoinGecko API and is copied to the directory that contains the executable file. Due to technical difficulties and limited time, the program does not retrieve the data from the API at execution. All the information is pre-downloaded and stored in `src/data` folder and is transferred to the appropriate directory when the program is built. In the future I might modify the program to either retrieve the data online at runtime, or write a bash script to run `curl` commands and comminucate with `Terade`. 

Command used to download one of the data files:

```
curl -X 'GET' 'https://api.coingecko.com/api/v3/coins/bitcoin/market_chart/range?id=bitcoin&vs_currency=usd&from=&1514851200to=1577923200' > data/bitcoin.json
```

* **[Nlohmann/JSON: JSON for Modern C++](https://github.com/nlohmann/json)** 

I used this JSON library to parse the data from the CoinGeko API and also to save and load the state of the simulation.

* **NCurses**

`view.h` defines an interface for the UI of the program. The `view_curses` class implements this interface and uses the NCurses library to present the data unto the console. Other classes could also implement the `view` interface and use different ways to display the data. For instance, to display the data using the `SDL` library, we would declare the following class,

```cpp
class view_sdl: public view {
	// override all the necessary functions
}
```

and set an instance of the `view_sdl` as the main view in the game object:

```cpp
g.set_view(std::unique_ptr<view>(new view_sdl));
```

## Build & Run

### Requirements

* **C++17**

The ranged-for loops used to iterate through map elements, use in-place unpacking which is not supported in earlier versions of c++.

```cpp
for (const auto& [key, value]: mymap) { }
```

* **CMake 3.11+**

`FetchContent` is not supported in earlier versions of CMake.

* **NCurses**

NCurses is probably already installed on most Linux distributions. Here are some tutorials on how to install NCurses on [MacOS](https://formulae.brew.sh/formula/ncurses), [Windows](https://e-l.unifi.it/pluginfile.php/805205/mod_resource/content/0/ncurses%20installation%20-%20en.pdf), and [Linux](https://www.cyberciti.biz/faq/linux-install-ncurses-library-headers-on-debian-ubuntu-centos-fedora/).

### Build

```
git clone https://github.com/ramtintjb/terade
cd terade
cmake -B build
cd build
make
cd src
./Terade
```

## Credits

I want to give special thanks to [David Parillo](https://github.com/daveparillo), who guided me at every step of the way and shared best practices and great resources with me.

## License

<img align="right" src="https://opensource.org/trademarks/opensource/OSI-Approved-License-100x137.png">

The project is licensed under the [MIT License](https://opensource.org/licenses/MIT):

Copyright &copy; 2022 Ramtin Tajbakhsh
