#ifndef _LINUX_DAX_H
#define _LINUX_DAX_H

#include <linux/fs.h>
#include <linux/mm.h>
#include <asm/pgtable.h>

ssize_t dax_do_io(int rw, struct kiocb *iocb, struct inode *inode,
                  const struct iovec *iov, loff_t pos, unsigned long nr_segs,
                  get_block_t get_block, dio_iodone_t end_io, int flags);
int dax_clear_sectors(struct block_device *bdev, sector_t _sector, long _size);
int dax_zero_page_range(struct inode *, loff_t from, unsigned len, get_block_t);
int dax_truncate_page(struct inode *, loff_t from, get_block_t);
int dax_fault(struct vm_area_struct *, struct vm_fault *, get_block_t,
		dax_iodone_t);
int __dax_fault(struct vm_area_struct *, struct vm_fault *, get_block_t,
		dax_iodone_t);

#ifdef CONFIG_FS_DAX
struct page *read_dax_sector(struct block_device *bdev, sector_t n);
#else
static inline struct page *read_dax_sector(struct block_device *bdev,
		sector_t n)
{
	return ERR_PTR(-ENXIO);
}
#endif

#ifdef CONFIG_TRANSPARENT_HUGEPAGE
int dax_pmd_fault(struct vm_area_struct *, unsigned long addr, pmd_t *,
				unsigned int flags, get_block_t, dax_iodone_t);
int __dax_pmd_fault(struct vm_area_struct *, unsigned long addr, pmd_t *,
				unsigned int flags, get_block_t, dax_iodone_t);
#else
static inline int dax_pmd_fault(struct vm_area_struct *vma, unsigned long addr,
				pmd_t *pmd, unsigned int flags, get_block_t gb,
				dax_iodone_t di)
{
	return VM_FAULT_FALLBACK;
}
#define __dax_pmd_fault dax_pmd_fault
#endif
int dax_pfn_mkwrite(struct vm_area_struct *, struct vm_fault *);
#define dax_mkwrite(vma, vmf, gb, iod)		dax_fault(vma, vmf, gb, iod)
#define __dax_mkwrite(vma, vmf, gb, iod)	__dax_fault(vma, vmf, gb, iod)

static inline bool vma_is_dax(struct vm_area_struct *vma)
{
	return vma->vm_file && IS_DAX(vma->vm_file->f_mapping->host);
}

static inline bool dax_mapping(struct address_space *mapping)
{
	return mapping->host && IS_DAX(mapping->host);
}

struct writeback_control;
int dax_writeback_mapping_range(struct address_space *mapping,
		struct block_device *bdev, struct writeback_control *wbc);
#endif
