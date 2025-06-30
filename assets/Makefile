ASSETS_APK := ../tmp/split_base_assets.apk
UNZIP_DIR := ../tmp/split_base_assets
EXPORT_DIR := ../tmp/split_base_assets_export
ASSETSTUDIO_ZIP := ../tmp/AssetStudioModCLI.zip
ASSETSTUDIO_DIR := ../tmp/AssetStudioModCLI
ASSETSTUDIO_VERSION := v0.18.0
ifeq ($(shell uname), Darwin)
	ASSETSTUDIO_URL := https://github.com/aelurum/AssetStudio/releases/download/$(ASSETSTUDIO_VERSION)/AssetStudioModCLI_net6_mac64.zip
else ifeq ($(shell uname), Linux)
	ASSETSTUDIO_URL := https://github.com/aelurum/AssetStudio/releases/download/$(ASSETSTUDIO_VERSION)/AssetStudioModCLI_net6_linux64.zip
else
	ASSETSTUDIO_URL := https://github.com/aelurum/AssetStudio/releases/download/$(ASSETSTUDIO_VERSION)/AssetStudioModCLI_net6_win64.zip
endif
IMAGE_DIR := image

.PHONY: all
all: $(IMAGE_DIR)/LevelUp.png $(IMAGE_DIR)/GoldBox1.png

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
	unzip -o $(ASSETS_APK) "assets/bin/Data/[0-9]*" -d $(UNZIP_DIR)/0-9
	unzip -o $(ASSETS_APK) "assets/bin/Data/[a-z]*" -d $(UNZIP_DIR)/a-z

.PHONY: asset
asset: $(EXPORT_DIR)
$(EXPORT_DIR): $(ASSETSTUDIO_DIR) $(UNZIP_DIR)
	./$(ASSETSTUDIO_DIR)/AssetStudioModCLI $(UNZIP_DIR)/0-9 -t tex2d -o $(EXPORT_DIR)
	./$(ASSETSTUDIO_DIR)/AssetStudioModCLI $(UNZIP_DIR)/a-z -t tex2d -o $(EXPORT_DIR)

$(EXPORT_DIR)/atlas_ui1.png: $(EXPORT_DIR)
$(EXPORT_DIR)/atlas_img.png: $(EXPORT_DIR)

$(IMAGE_DIR)/LevelUp.png: $(EXPORT_DIR)/atlas_ui1.png
	magick $< -crop 51x51+386+832 -resize 55% -channel RGBA -fx "a < 1 ? #00FF00 : u" +repage -strip -alpha off $@
$(IMAGE_DIR)/GoldBox1.png: $(EXPORT_DIR)/atlas_img.png
	magick $< -crop 247x160+1416+1088 -resize 64% -channel RGBA -fx "a < 1 ? #00FF00 : u" +repage -strip -alpha off $@
