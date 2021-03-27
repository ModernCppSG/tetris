" Add to .vimrc to enable project-specific vimrc

set exrc
set secure

" exrc allows loading local executing local rc files.
" secure disallows the use of :autocmd, shell and write commands in local .vimrc files.

let g:ale_c_clang_options="-I/path/to/your/project"
let g:ale_cpp_clang_options="-I/path/to/your/project"
