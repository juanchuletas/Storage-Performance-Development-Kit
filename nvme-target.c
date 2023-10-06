#include <spdk/nvme.h>
#include <spdk/nvme_o.h>

int main() {
  //to create an NVMe-oF target.
  struct spdk_nvme_tgt *tgt = spdk_nvme_tgt_create();

  // Adds an NVMe device to the target.
  struct spdk_nvme_ctrlr *ctrlr = spdk_nvme_ctrlr_get_first();
  spdk_nvme_tgt_add_ctrlr(tgt, ctrlr);

  // Listen to a specific network port.
  struct spdk_sockaddr_in addr = {};
  addr.sin_family = AF_INET;
  addr.sin_port = htons(PORT);
  addr.sin_addr.s_addr = INADDR_ANY;
  spdk_nvme_tgt_listen(tgt, addr);

  // Starts the target.
  spdk_nvme_tgt_start(tgt);

  // Waits for the target to stop.
  spdk_nvme_tgt_stop(tgt);

  return 0;
}

