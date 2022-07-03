/*
 * dfs ctrl
 *
*/
#include <rtdbg.h>
#include <rtthread.h>
#include <rtdevice.h>
#include <string.h>
#include <dfs_fs.h>

#include <device_config.h>

/*
 * int mnt_sd_init(const char *device_name, const char *path)
 * input: const char *device_name; block device, examp: "sd0"
 * input: const char *path; mount path, example: "/"
 * return: ret; 0: success; -1: failed
 */
int mnt_sd_init(char *device_name, char *path)
{
    int ret = 0;
    rt_thread_mdelay(100);   //delay for SD card ready
    ret = dfs_mount(device_name, path, "elm", 0, 0);

    return ret;
}

/*
 * int mnt_sd_deinit(const char *path)
 * input: const char *path; mount path, example: "/"
 * return: ret; 0: success; -1: failed
 */
int mnt_sd_deinit(char *path)
{
    int ret = 0;
    ret = dfs_unmount(path);

    return ret;
}
