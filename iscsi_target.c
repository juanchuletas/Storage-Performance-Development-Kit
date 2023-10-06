#include <spdk/event.h>
#include <spdk/scsi.h>
#include <spdk/iscsi.h>

int main() {
  // To create an iSCSI target.
  struct spdk_iscsi_tgt *tgt = spdk_iscsi_tgt_create();

  // Adds a bdev to the target.
  struct spdk_bdev *bdev = spdk_bdev_get_by_name("malloc0");
  spdk_iscsi_tgt_add_bdev(tgt, bdev);

  // Listen to a specific network port.
  struct spdk_sockaddr_in addr = {};
  addr.sin_family = AF_INET;
  addr.sin_port = htons(PORT);
  addr.sin_addr.s_addr = INADDR_ANY;
  spdk_iscsi_tgt_listen(tgt, addr);

  // Starts the target.
  spdk_iscsi_tgt_start(tgt);

  // Waits for the target to stop.
  spdk_iscsi_tgt_stop(tgt);

  return 0;
}
