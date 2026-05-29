# SHA256 SAMP Plugin

This plugin adds support for SHA-256 string hashing to the SA-MP server, implemented using the picosha2 library.

### Usage

`
Crypto_SHA256(const input[], output[], len);
`

### Arguments

* `input[]`: The input string to hash.
* `output[]`: The buffer to store the hex-encoded result.
* `len`: The size of the output buffer. (Must be at least 65 bytes: 64 characters + \0).

### Returns

* 1: Success.
* 0: Failure.

### Example
```
new hash[65];
Crypto_SHA256("hello world", hash, sizeof(hash));
printf("Hash: %s", hash);
```

# Build

`
git clone --recurse-submodules https://github.com/1therealcloud/samp-sha256
`

`
cd samp-sha256
`

## Windows
```bash
cmake -B build -A Win32
cmake --build build --config Release
```

## Linux

```bash
cmake -B build
cmake --build build --config Release
```

### Dependency Installation

**Arch Linux**

```bash
# Enable multilib
sed -i '/^#\[multilib\]/s/^#//; /^#Include = \/etc\/pacman.d\/mirrorlist/s/^#//' /etc/pacman.conf

# Install packages
pacman -Sy
pacman -S git gcc gcc-multilib lib32-gcc-libs cmake make
```

**Debian / Ubuntu**

```bash
sudo apt update
sudo apt install -y git build-essential gcc-multilib g++-multilib cmake
```

**Fedora**

```bash
sudo dnf groupinstall -y "Development Tools"
sudo dnf install -y git glibc-devel.i686 libgcc.i686 cmake
```