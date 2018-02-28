#!/bin/bash
#

# Extract next version from platform.txt
next=`sed -n -E 's/version=([0-9.]+)/\1/p' ../platform.txt`

ver="${next}"
package_name=mego-$ver
prev_release="2.3.0"

echo "Version: $ver"
echo "Package name: $package_name"

PKG_URL="https://github.com/QWaveSystems/Mego-Arduino/releases/download/${ver}/$package_name.zip"

echo "Package: $PKG_URL"
echo "Docs: $DOC_URL"

pushd ..
# Create directory for the package
outdir=package/versions/$ver/$package_name
srcdir=$PWD
rm -rf package/versions/$ver
mkdir -p $outdir

# Some files should be excluded from the package
cat << EOF > exclude.txt
.git
.gitignore
.travis.yml
package
doc
EOF
# Also include all files which are ignored by git
git ls-files --other --directory >> exclude.txt
# Now copy files to $outdir
rsync -a --exclude-from 'exclude.txt' $srcdir/ $outdir/
rm exclude.txt

# Get additional libraries (TODO: add them as git submodule or subtree?)

# SoftwareSerial library
curl -L -o SoftwareSerial.zip https://github.com/plerup/espsoftwareserial/archive/3.3.1.zip
unzip -q SoftwareSerial.zip
rm -rf SoftwareSerial.zip
mv espsoftwareserial-* SoftwareSerial
mv SoftwareSerial $outdir/libraries

# Copy qwavesys files
cp -r $srcdir/qwavesys/libraries/* $outdir/libraries
cp -r $srcdir/qwavesys/variants $outdir

# For compatibility, on OS X we need GNU sed which is usually called 'gsed'
#if [ "$(uname)" == "Darwin" ]; then
#    SED=gsed
#else
#    SED=sed
#fi

SED=sed

# Do some replacements in platform.txt file, which are required because IDE
# handles tool paths differently when package is installed in hardware folder
cat $srcdir/platform.txt | \
$SED 's/runtime.tools.xtensa-lx106-elf-gcc.path={runtime.platform.path}\/tools\/xtensa-lx106-elf//g' | \
$SED 's/runtime.tools.esptool.path={runtime.platform.path}\/tools\/esptool//g' | \
$SED 's/tools.esptool.path={runtime.platform.path}\/tools\/esptool/tools.esptool.path=\{runtime.tools.esptool.path\}/g' | \
$SED 's/tools.mkspiffs.path={runtime.platform.path}\/tools\/mkspiffs/tools.mkspiffs.path=\{runtime.tools.mkspiffs.path\}/g' |\
$SED 's/recipe.hooks.core.prebuild.1.pattern.*//g' \
 > $outdir/platform.txt

# Put core version and short hash of git version into core_version.h
ver_define=`echo $plain_ver | tr "[:lower:].\055" "[:upper:]_"`
echo Ver define: $ver_define
echo \#define ARDUINO_ESP8266_GIT_VER 0x`git rev-parse --short=8 HEAD 2>/dev/null` >$outdir/cores/esp8266/core_version.h
echo \#define ARDUINO_ESP8266_RELEASE_$ver_define >>$outdir/cores/esp8266/core_version.h
echo \#define ARDUINO_ESP8266_RELEASE \"$ver_define\" >>$outdir/cores/esp8266/core_version.h

# Zip the package
pushd package/versions/$ver
echo "Making $package_name.zip"
zip -qr $package_name.zip $package_name
rm -rf $package_name

# Calculate SHA sum and size
sha=`shasum -a 256 $package_name.zip | cut -f 1 -d ' '`
size=`/bin/ls -l $package_name.zip | awk '{print $5}'`
echo Size: $size
echo SHA-256: $sha

echo "Making package_mego_index.json"

jq_arg=".packages[0].platforms[0].version = \"$ver\" | \
    .packages[0].platforms[0].url = \"$PKG_URL\" |\
    .packages[0].platforms[0].archiveFileName = \"$package_name.zip\""

if [ -z "$is_nightly" ]; then
    jq_arg="$jq_arg |\
        .packages[0].platforms[0].size = \"$size\" |\
        .packages[0].platforms[0].checksum = \"SHA-256:$sha\""
fi

if [ ! -z "$DOC_URL" ]; then
    jq_arg="$jq_arg |\
        .packages[0].platforms[0].help.online = \"$DOC_URL\""
fi

cat $srcdir/package/package_mego_index.template.json | \
    jq "$jq_arg" > package_mego_index.json

echo "Previous release: $prev_release"

# Download previous release
echo "Downloading base package: $prev_release"
old_json=package_mego_index_stable.json
curl -L -o $old_json "https://github.com/QWaveSystems/Mego-Arduino/releases/download/${prev_release}/package_mego_index.json"
new_json=package_mego_index.json

set +e
python ../../merge_packages.py $new_json $old_json >tmp && mv tmp $new_json && rm $old_json

popd
popd
