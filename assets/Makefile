ASSETS_APK := split_base_assets.apk
UNZIP_DIR := split_base_assets
EXPORT_DIR := split_base_assets_export
ASSETSTUDIO_ZIP := AssetStudioModCLI.zip
ASSETSTUDIO_DIR := AssetStudioModCLI
ASSETSTUDIO_VERSION := v0.18.0
ifeq ($(shell uname), Darwin)
	ASSETSTUDIO_URL := https://github.com/aelurum/AssetStudio/releases/download/$(ASSETSTUDIO_VERSION)/AssetStudioModCLI_net6_mac64.zip
else ifeq ($(shell uname), Linux)
	ASSETSTUDIO_URL := https://github.com/aelurum/AssetStudio/releases/download/$(ASSETSTUDIO_VERSION)/AssetStudioModCLI_net6_linux64.zip
else
	ASSETSTUDIO_URL := https://github.com/aelurum/AssetStudio/releases/download/$(ASSETSTUDIO_VERSION)/AssetStudioModCLI_net6_win64.zip
endif

$(ASSETSTUDIO_ZIP):
	curl -L $(ASSETSTUDIO_URL) -o $(ASSETSTUDIO_ZIP)

$(ASSETSTUDIO_DIR): $(ASSETSTUDIO_ZIP)
	mkdir -p $(ASSETSTUDIO_DIR)
	unzip -o $(ASSETSTUDIO_ZIP) -d $(ASSETSTUDIO_DIR)
	chmod a+x $(ASSETSTUDIO_DIR)/AssetStudioModCLI

.PHONY: unpack
unpack: $(UNZIP_DIR)

$(UNZIP_DIR): $(ASSETS_APK)
	mkdir -p $(UNZIP_DIR)
	unzip -o $(ASSETS_APK) -d $(UNZIP_DIR)

.PHONY: assetstudio
assetstudio: $(ASSETSTUDIO_DIR) $(UNZIP_DIR)
	./$(ASSETSTUDIO_DIR)/AssetStudioModCLI $(UNZIP_DIR)/assets/bin/Data/ -t tex2d -o $(EXPORT_DIR)
