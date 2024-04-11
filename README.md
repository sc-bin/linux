# Linux Kernel Source Tree

Kernel source tree for AvaotaSBC-provided kernel builds.

## Kernel Branches
- [Linux 5.15](https://github.com/AvaotaSBC/linux/tree/linux-5.15)

## AutoCI Branch Update

In the Kernel repo, we use Github Action to release kernel source code, and provide latest update of kernel

This GitHub Actions workflow aims to merge different versions of the Linux kernel under specific conditions—either when code is pushed to the `main` branch or when a `pull_request` is created with the target branch being `main`.

Here's a breakdown of its purpose:

1. When the triggering conditions are met, the workflow starts executing.
2. It runs on the latest version of Ubuntu.
3. It uses the `actions/checkout@v3` action to fetch the latest version of the code repository.
4. Git username and email are set to "GitHub Actions" and "actions@github.com" respectively.
5. The `init.sh` script is executed to merge version 5.15 of the Linux kernel. This script requires parameters specifying the URL for downloading the kernel, the patch file, version number, and branch name.
6. The `ad-m/github-push-action@master` action is utilized to push the merged code to a branch named `linux-5.15`, with the specified directory being `kernel/dst/linux-5.15/linux-5.15`.

In summary, this workflow automates the merging of specified versions of the Linux kernel and pushes the merged code to the corresponding branch, facilitating automated code management and updates.

## How to use init.sh

This shell script `init.sh` performs several tasks related to managing Linux kernel source code:

1. It initializes various variables such as `HOST_ARCH`, `ROOT_PATH`, `DATE`, `PATCH_PATH`, and `TARBALL`.
2. It sets default parameters using the `default_param` function and parses command-line arguments using the `parseargs` function.
3. It displays the system architecture on which the script is running.
4. It creates a directory for the specified kernel version and downloads the corresponding kernel source code from the provided URL.
5. It unarchives the downloaded kernel source code and copies BSP (Board Support Package) files into the kernel directory.
6. It applies patches to the kernel source code.
7. It clones an old version of the kernel from a Git repository and merges it with the newly downloaded kernel.
8. Finally, it commits the changes to the Git repository with a message containing the current date and "Kernel update".

Overall, this script automates the process of downloading, patching, and merging Linux kernel source code for development or customization purposes.

```
Usage: init [OPTIONS]
Build Kernel repo.

Options:
  -u, --url        URL               The url of kernel
  -v, --version    VERSION           The version of kernel
  -p, --patch      PATCHFILE         The patch file of kernel
  -b, --branch     BRANCH NAME       The branch of dst kernel
  -h, --help                         Show command help.
```
