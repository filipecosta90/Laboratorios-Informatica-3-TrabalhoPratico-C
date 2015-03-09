if &cp | set nocp | endif
let s:cpo_save=&cpo
set cpo&vim
nmap gx <Plug>NetrwBrowseX
nnoremap <silent> <Plug>NetrwBrowseX :call netrw#NetrwBrowseX(expand("<cWORD>"),0)
let &cpo=s:cpo_save
unlet s:cpo_save
set autoindent
set autowrite
set backspace=indent,eol,start
set copyindent
set expandtab
set fileencodings=ucs-bom,utf-8,default,latin1
set ignorecase
set listchars=tab:--,trail:.,nbsp:.
set modelines=0
set pastetoggle=<C-P>
set runtimepath=~/.vim,~/.vim/bundle/vim-colors-solarized,/usr/share/vim/vimfiles,/usr/share/vim/vim73,/usr/share/vim/vimfiles/after,~/.vim/after
set shiftround
set shiftwidth=2
set smartcase
set smarttab
set splitbelow
set splitright
set tabstop=2
set tags=./tags;
set title
set visualbell
set window=0
" vim: set ft=vim :
