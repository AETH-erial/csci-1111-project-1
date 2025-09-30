SRC = main.c
OUTDIR = build

$(shell mkdir -p $(OUTDIR))

all: native linux-arm64 windows linux-x86_64 mac-arm64 mac-x86_64

# Native build 
native:
	@echo "Building native popquiz..."
	gcc $(SRC) -o $(OUTDIR)/popquiz_native

# Linux ARM64 build
linux-arm64:
	@echo "Building Linux ARM64..."
	aarch64-linux-gnu-gcc $(SRC) -o $(OUTDIR)/popquiz_linux_arm64

# Linux x86_64 build
linux-x86_64:
	@echo "Building Linux x86_64..."
	gcc -m64 $(SRC) -o $(OUTDIR)/popquiz_linux_x86_64

# Windows x86_64 build (outputs .exe)
windows:
	@echo "Building Windows x86_64..."
	x86_64-w64-mingw32-gcc $(SRC) -o $(OUTDIR)/popquiz_windows.exe

# macOS ARM64 build (Apple Silicon)
mac-arm64:
	@echo "Building macOS ARM64..."
	arm64-apple-darwin23-gcc $(SRC) -o $(OUTDIR)/popquiz_mac_arm64

# macOS x86_64 build (Intel Macs)
mac-x86_64:
	@echo "Building macOS x86_64..."
	x86_64-apple-darwin23-gcc $(SRC) -o $(OUTDIR)/popquiz_mac_x86_64

clean:
	rm -rf $(OUTDIR)
