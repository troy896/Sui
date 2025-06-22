#!/sbin/sh
MODDIR=${0%/*}
MODULES=$(dirname "$MODDIR")

uninstall() {
  chmod 700 "$MODDIR"/bin/uninstall
  "$MODDIR"/bin/uninstall "$MODDIR"
  rm -rf "/data/adb/sui"
}

if [ -d "$MODULES/zygisk_sui" ]; then
  if [ -f "$MODULES/zygisk_sui/remove" ]; then
    uninstall
  fi
else
  uninstall
fi
