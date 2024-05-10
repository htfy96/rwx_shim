#pragma once

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Define a section attribute for the RWX shim section.
 *
 * This macro defines a section attribute for the RWX shim section.
 * The RWX shim section is a special section in memory that allows for read,
 * write, and execute access.
 *
 * @param[in] section_name The name of the section to which the attribute is
 * applied.
 */
#define RWX_SHIM_SECTION_ATTR __attribute__((section("rwx_shim")))

/**
 * @brief Ensures that the RWX shim section is linked.
 *
 * This function ensures that the RWX shim section is linked in memory.
 * The RWX shim section is a special section that allows for read, write, and
 * execute access.
 *
 * This function is a no-op at runtime.
 */
extern void _ensure_rwx_shm_linked(void) RWX_SHIM_SECTION_ATTR;
;

/**
 * @brief Get the start address of the RWX shim section.
 *
 * This function retrieves the start address of the RWX shim section.
 * The RWX shim section is a special section in memory that allows for read,
 * write, and execute access.
 *
 * @return A pointer to the start address of the RWX shim section.
 */
extern void *_get_rwx_shim_start(void)
    __attribute__((section("rwx_shim_meta")));
;
/**
 * @brief Get the end address of the RWX shim section.
 *
 * This function retrieves the end address of the RWX shim section.
 * The RWX shim section is a special section in memory that allows for read,
 * write, and execute access.
 *
 * @return A pointer to the end address of the RWX shim section.
 */
extern void *_get_rwx_shim_end(void) __attribute__((section("rwx_shim_meta")));
;

/**
Disallows writes to the RWX shim.
*/
extern void seal_rwx_shim(void);
#ifdef __cplusplus
}
#endif