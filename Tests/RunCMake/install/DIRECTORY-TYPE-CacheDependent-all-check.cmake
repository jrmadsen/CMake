set(_check_files
  [[myshare]]
  [[myshare/dir]]
  [[myshare/dir/empty\.txt]]
  [[myshare/doc]]
  [[myshare/doc/dir]]
  [[myshare/doc/dir/empty\.txt]]
  [[myshare/info]]
  [[myshare/info/dir]]
  [[myshare/info/dir/empty\.txt]]
  [[myshare/locale]]
  [[myshare/locale/dir]]
  [[myshare/locale/dir/empty\.txt]]
  [[myshare/man]]
  [[myshare/man/dir]]
  [[myshare/man/dir/empty.txt]]
  [[myvar]]
  [[myvar/dir]]
  [[myvar/dir/empty\.txt]]
  [[myvar/run]]
  [[myvar/run/dir]]
  [[myvar/run/dir/empty\.txt]]
  )
check_installed("^${_check_files}$")
