#!/bin/sh
set -e

IMG=filesystem_sd.img

rm -f ${IMG}
../../Standalone/mkfs ${IMG} 32 65535
../../Standalone/ucp ${IMG} <<EOF
cd /
mkdir games
chmod 0755 /
chmod 0755 games

cd /games
bget ../../Applications/games/conway conway
chmod 755 conway

EOF

../../Standalone/fsck -a ${IMG}


