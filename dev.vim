if &cp | set nocp | endif
let s:cpo_save=&cpo
set cpo&vim
inoremap <silent> <Plug>(altr-forward) :call altr#forward()
cnoremap <silent> <Plug>(altr-forward) :call altr#forward()
inoremap <silent> <Plug>(altr-back) :call altr#back()
cnoremap <silent> <Plug>(altr-back) :call altr#back()
inoremap <silent> <C-Tab> =UltiSnips#ListSnippets()
inoremap <expr> <Plug>(fzf-complete-buffer-line) fzf#vim#complete#buffer_line()
inoremap <expr> <Plug>(fzf-complete-line) fzf#vim#complete#line()
inoremap <expr> <Plug>(fzf-complete-file-ag) fzf#vim#complete#path("ag -l -g ''")
inoremap <expr> <Plug>(fzf-complete-file) fzf#vim#complete#path("find . -path '*/\.*' -prune -o -type f -print -o -type l -print | sed 's:^..::'")
inoremap <expr> <Plug>(fzf-complete-path) fzf#vim#complete#path("find . -path '*/\.*' -prune -o -print | sed '1d;s:^..::'")
inoremap <expr> <Plug>(fzf-complete-word) fzf#vim#complete#word()
vmap  <Plug>VisualIncrement
snoremap <silent>  c
nnoremap  h
xnoremap  h
onoremap  h
xnoremap <silent> 	 :call UltiSnips#SaveLastVisualSelection()gvs
snoremap <silent> 	 :call UltiSnips#ExpandSnippet()
noremap <NL> j
noremap  k
noremap  l
snoremap  "_c
vmap  <Plug>VisualDecrement
nnoremap  [s1z=
map   \
nnoremap ' `
vnoremap . :normal .
nmap <, <Plug>Argumentative_MoveLeft
nmap >, <Plug>Argumentative_MoveRight
xnoremap @q :normal @q
xnoremap <silent> <expr> A targets#e('A')
onoremap <silent> Ala :call targets#o('alA', v:count1)
onoremap <silent> Ana :call targets#o('anA', v:count1)
onoremap <silent> Aa :call targets#o('acA', v:count1)
onoremap <silent> AL$ :call targets#o('$LA', v:count1)
onoremap <silent> AN$ :call targets#o('$NA', v:count1)
onoremap <silent> Al$ :call targets#o('$lA', v:count1)
onoremap <silent> An$ :call targets#o('$nA', v:count1)
onoremap <silent> A$ :call targets#o('$cA', v:count1)
onoremap <silent> AL& :call targets#o('&LA', v:count1)
onoremap <silent> AN& :call targets#o('&NA', v:count1)
onoremap <silent> Al& :call targets#o('&lA', v:count1)
onoremap <silent> An& :call targets#o('&nA', v:count1)
onoremap <silent> A& :call targets#o('&cA', v:count1)
onoremap <silent> AL| :call targets#o('|LA', v:count1)
onoremap <silent> AN| :call targets#o('|NA', v:count1)
onoremap <silent> Al| :call targets#o('|lA', v:count1)
onoremap <silent> An| :call targets#o('|nA', v:count1)
onoremap <silent> A| :call targets#o('|cA', v:count1)
onoremap <silent> AL\ :call targets#o('\LA', v:count1)
onoremap <silent> AN\ :call targets#o('\NA', v:count1)
onoremap <silent> Al\ :call targets#o('\lA', v:count1)
onoremap <silent> An\ :call targets#o('\nA', v:count1)
onoremap <silent> A\ :call targets#o('\cA', v:count1)
onoremap <silent> AL/ :call targets#o('/LA', v:count1)
onoremap <silent> AN/ :call targets#o('/NA', v:count1)
onoremap <silent> Al/ :call targets#o('/lA', v:count1)
onoremap <silent> An/ :call targets#o('/nA', v:count1)
onoremap <silent> A/ :call targets#o('/cA', v:count1)
onoremap <silent> AL# :call targets#o('#LA', v:count1)
onoremap <silent> AN# :call targets#o('#NA', v:count1)
onoremap <silent> Al# :call targets#o('#lA', v:count1)
onoremap <silent> An# :call targets#o('#nA', v:count1)
onoremap <silent> A# :call targets#o('#cA', v:count1)
onoremap <silent> AL* :call targets#o('*LA', v:count1)
onoremap <silent> AN* :call targets#o('*NA', v:count1)
onoremap <silent> Al* :call targets#o('*lA', v:count1)
onoremap <silent> An* :call targets#o('*nA', v:count1)
onoremap <silent> A* :call targets#o('*cA', v:count1)
onoremap <silent> AL_ :call targets#o('_LA', v:count1)
onoremap <silent> AN_ :call targets#o('_NA', v:count1)
onoremap <silent> Al_ :call targets#o('_lA', v:count1)
onoremap <silent> An_ :call targets#o('_nA', v:count1)
onoremap <silent> A_ :call targets#o('_cA', v:count1)
onoremap <silent> AL~ :call targets#o('~LA', v:count1)
onoremap <silent> AN~ :call targets#o('~NA', v:count1)
onoremap <silent> Al~ :call targets#o('~lA', v:count1)
onoremap <silent> An~ :call targets#o('~nA', v:count1)
onoremap <silent> A~ :call targets#o('~cA', v:count1)
onoremap <silent> AL= :call targets#o('=LA', v:count1)
onoremap <silent> AN= :call targets#o('=NA', v:count1)
onoremap <silent> Al= :call targets#o('=lA', v:count1)
onoremap <silent> An= :call targets#o('=nA', v:count1)
onoremap <silent> A= :call targets#o('=cA', v:count1)
onoremap <silent> AL- :call targets#o('-LA', v:count1)
onoremap <silent> AN- :call targets#o('-NA', v:count1)
onoremap <silent> Al- :call targets#o('-lA', v:count1)
onoremap <silent> An- :call targets#o('-nA', v:count1)
onoremap <silent> A- :call targets#o('-cA', v:count1)
onoremap <silent> AL+ :call targets#o('+LA', v:count1)
onoremap <silent> AN+ :call targets#o('+NA', v:count1)
onoremap <silent> Al+ :call targets#o('+lA', v:count1)
onoremap <silent> An+ :call targets#o('+nA', v:count1)
onoremap <silent> A+ :call targets#o('+cA', v:count1)
onoremap <silent> AL: :call targets#o(':LA', v:count1)
onoremap <silent> AN: :call targets#o(':NA', v:count1)
onoremap <silent> Al: :call targets#o(':lA', v:count1)
onoremap <silent> An: :call targets#o(':nA', v:count1)
onoremap <silent> A: :call targets#o(':cA', v:count1)
onoremap <silent> AL; :call targets#o(';LA', v:count1)
onoremap <silent> AN; :call targets#o(';NA', v:count1)
onoremap <silent> Al; :call targets#o(';lA', v:count1)
onoremap <silent> An; :call targets#o(';nA', v:count1)
onoremap <silent> A; :call targets#o(';cA', v:count1)
onoremap <silent> AL. :call targets#o('.LA', v:count1)
onoremap <silent> AN. :call targets#o('.NA', v:count1)
onoremap <silent> Al. :call targets#o('.lA', v:count1)
onoremap <silent> An. :call targets#o('.nA', v:count1)
onoremap <silent> A. :call targets#o('.cA', v:count1)
onoremap <silent> AL, :call targets#o(',LA', v:count1)
onoremap <silent> AN, :call targets#o(',NA', v:count1)
onoremap <silent> Al, :call targets#o(',lA', v:count1)
onoremap <silent> An, :call targets#o(',nA', v:count1)
onoremap <silent> A, :call targets#o(',cA', v:count1)
onoremap <silent> AL` :call targets#o('`LA', v:count1)
onoremap <silent> AN` :call targets#o('`NA', v:count1)
onoremap <silent> Al` :call targets#o('`lA', v:count1)
onoremap <silent> An` :call targets#o('`nA', v:count1)
onoremap <silent> A` :call targets#o('`cA', v:count1)
onoremap <silent> AL' :call targets#o('''LA', v:count1)
onoremap <silent> AN' :call targets#o('''NA', v:count1)
onoremap <silent> Al' :call targets#o('''lA', v:count1)
onoremap <silent> An' :call targets#o('''nA', v:count1)
onoremap <silent> A' :call targets#o('''cA', v:count1)
onoremap <silent> AL" :call targets#o('"LA', v:count1)
onoremap <silent> AN" :call targets#o('"NA', v:count1)
onoremap <silent> Al" :call targets#o('"lA', v:count1)
onoremap <silent> An" :call targets#o('"nA', v:count1)
onoremap <silent> A" :call targets#o('"cA', v:count1)
onoremap <silent> Alt :call targets#o('tlA', v:count1)
onoremap <silent> Ant :call targets#o('tnA', v:count1)
onoremap <silent> At :call targets#o('tcA', v:count1)
onoremap <silent> Al> :call targets#o('>lA', v:count1)
onoremap <silent> An> :call targets#o('>nA', v:count1)
onoremap <silent> A> :call targets#o('>cA', v:count1)
onoremap <silent> Al< :call targets#o('<lA', v:count1)
onoremap <silent> An< :call targets#o('<nA', v:count1)
onoremap <silent> A< :call targets#o('<cA', v:count1)
onoremap <silent> Al] :call targets#o(']lA', v:count1)
onoremap <silent> An] :call targets#o(']nA', v:count1)
onoremap <silent> A] :call targets#o(']cA', v:count1)
onoremap <silent> Al[ :call targets#o('[lA', v:count1)
onoremap <silent> An[ :call targets#o('[nA', v:count1)
onoremap <silent> A[ :call targets#o('[cA', v:count1)
onoremap <silent> AlB :call targets#o('BlA', v:count1)
onoremap <silent> AnB :call targets#o('BnA', v:count1)
onoremap <silent> AB :call targets#o('BcA', v:count1)
onoremap <silent> Al} :call targets#o('}lA', v:count1)
onoremap <silent> An} :call targets#o('}nA', v:count1)
onoremap <silent> A} :call targets#o('}cA', v:count1)
onoremap <silent> Al{ :call targets#o('{lA', v:count1)
onoremap <silent> An{ :call targets#o('{nA', v:count1)
onoremap <silent> A{ :call targets#o('{cA', v:count1)
onoremap <silent> Alb :call targets#o('blA', v:count1)
onoremap <silent> Anb :call targets#o('bnA', v:count1)
onoremap <silent> Ab :call targets#o('bcA', v:count1)
onoremap <silent> Al) :call targets#o(')lA', v:count1)
onoremap <silent> An) :call targets#o(')nA', v:count1)
onoremap <silent> A) :call targets#o(')cA', v:count1)
onoremap <silent> Al( :call targets#o('(lA', v:count1)
onoremap <silent> An( :call targets#o('(nA', v:count1)
onoremap <silent> A( :call targets#o('(cA', v:count1)
xnoremap <silent> <expr> I targets#e('I')
onoremap <silent> Ila :call targets#o('alI', v:count1)
onoremap <silent> Ina :call targets#o('anI', v:count1)
onoremap <silent> Ia :call targets#o('acI', v:count1)
onoremap <silent> IL$ :call targets#o('$LI', v:count1)
onoremap <silent> IN$ :call targets#o('$NI', v:count1)
onoremap <silent> Il$ :call targets#o('$lI', v:count1)
onoremap <silent> In$ :call targets#o('$nI', v:count1)
onoremap <silent> I$ :call targets#o('$cI', v:count1)
onoremap <silent> IL& :call targets#o('&LI', v:count1)
onoremap <silent> IN& :call targets#o('&NI', v:count1)
onoremap <silent> Il& :call targets#o('&lI', v:count1)
onoremap <silent> In& :call targets#o('&nI', v:count1)
onoremap <silent> I& :call targets#o('&cI', v:count1)
onoremap <silent> IL| :call targets#o('|LI', v:count1)
onoremap <silent> IN| :call targets#o('|NI', v:count1)
onoremap <silent> Il| :call targets#o('|lI', v:count1)
onoremap <silent> In| :call targets#o('|nI', v:count1)
onoremap <silent> I| :call targets#o('|cI', v:count1)
onoremap <silent> IL\ :call targets#o('\LI', v:count1)
onoremap <silent> IN\ :call targets#o('\NI', v:count1)
onoremap <silent> Il\ :call targets#o('\lI', v:count1)
onoremap <silent> In\ :call targets#o('\nI', v:count1)
onoremap <silent> I\ :call targets#o('\cI', v:count1)
onoremap <silent> IL/ :call targets#o('/LI', v:count1)
onoremap <silent> IN/ :call targets#o('/NI', v:count1)
onoremap <silent> Il/ :call targets#o('/lI', v:count1)
onoremap <silent> In/ :call targets#o('/nI', v:count1)
onoremap <silent> I/ :call targets#o('/cI', v:count1)
onoremap <silent> IL# :call targets#o('#LI', v:count1)
onoremap <silent> IN# :call targets#o('#NI', v:count1)
onoremap <silent> Il# :call targets#o('#lI', v:count1)
onoremap <silent> In# :call targets#o('#nI', v:count1)
onoremap <silent> I# :call targets#o('#cI', v:count1)
onoremap <silent> IL* :call targets#o('*LI', v:count1)
onoremap <silent> IN* :call targets#o('*NI', v:count1)
onoremap <silent> Il* :call targets#o('*lI', v:count1)
onoremap <silent> In* :call targets#o('*nI', v:count1)
onoremap <silent> I* :call targets#o('*cI', v:count1)
onoremap <silent> IL_ :call targets#o('_LI', v:count1)
onoremap <silent> IN_ :call targets#o('_NI', v:count1)
onoremap <silent> Il_ :call targets#o('_lI', v:count1)
onoremap <silent> In_ :call targets#o('_nI', v:count1)
onoremap <silent> I_ :call targets#o('_cI', v:count1)
onoremap <silent> IL~ :call targets#o('~LI', v:count1)
onoremap <silent> IN~ :call targets#o('~NI', v:count1)
onoremap <silent> Il~ :call targets#o('~lI', v:count1)
onoremap <silent> In~ :call targets#o('~nI', v:count1)
onoremap <silent> I~ :call targets#o('~cI', v:count1)
onoremap <silent> IL= :call targets#o('=LI', v:count1)
onoremap <silent> IN= :call targets#o('=NI', v:count1)
onoremap <silent> Il= :call targets#o('=lI', v:count1)
onoremap <silent> In= :call targets#o('=nI', v:count1)
onoremap <silent> I= :call targets#o('=cI', v:count1)
onoremap <silent> IL- :call targets#o('-LI', v:count1)
onoremap <silent> IN- :call targets#o('-NI', v:count1)
onoremap <silent> Il- :call targets#o('-lI', v:count1)
onoremap <silent> In- :call targets#o('-nI', v:count1)
onoremap <silent> I- :call targets#o('-cI', v:count1)
onoremap <silent> IL+ :call targets#o('+LI', v:count1)
onoremap <silent> IN+ :call targets#o('+NI', v:count1)
onoremap <silent> Il+ :call targets#o('+lI', v:count1)
onoremap <silent> In+ :call targets#o('+nI', v:count1)
onoremap <silent> I+ :call targets#o('+cI', v:count1)
onoremap <silent> IL: :call targets#o(':LI', v:count1)
onoremap <silent> IN: :call targets#o(':NI', v:count1)
onoremap <silent> Il: :call targets#o(':lI', v:count1)
onoremap <silent> In: :call targets#o(':nI', v:count1)
onoremap <silent> I: :call targets#o(':cI', v:count1)
onoremap <silent> IL; :call targets#o(';LI', v:count1)
onoremap <silent> IN; :call targets#o(';NI', v:count1)
onoremap <silent> Il; :call targets#o(';lI', v:count1)
onoremap <silent> In; :call targets#o(';nI', v:count1)
onoremap <silent> I; :call targets#o(';cI', v:count1)
onoremap <silent> IL. :call targets#o('.LI', v:count1)
onoremap <silent> IN. :call targets#o('.NI', v:count1)
onoremap <silent> Il. :call targets#o('.lI', v:count1)
onoremap <silent> In. :call targets#o('.nI', v:count1)
onoremap <silent> I. :call targets#o('.cI', v:count1)
onoremap <silent> IL, :call targets#o(',LI', v:count1)
onoremap <silent> IN, :call targets#o(',NI', v:count1)
onoremap <silent> Il, :call targets#o(',lI', v:count1)
onoremap <silent> In, :call targets#o(',nI', v:count1)
onoremap <silent> I, :call targets#o(',cI', v:count1)
onoremap <silent> IL` :call targets#o('`LI', v:count1)
onoremap <silent> IN` :call targets#o('`NI', v:count1)
onoremap <silent> Il` :call targets#o('`lI', v:count1)
onoremap <silent> In` :call targets#o('`nI', v:count1)
onoremap <silent> I` :call targets#o('`cI', v:count1)
onoremap <silent> IL' :call targets#o('''LI', v:count1)
onoremap <silent> IN' :call targets#o('''NI', v:count1)
onoremap <silent> Il' :call targets#o('''lI', v:count1)
onoremap <silent> In' :call targets#o('''nI', v:count1)
onoremap <silent> I' :call targets#o('''cI', v:count1)
onoremap <silent> IL" :call targets#o('"LI', v:count1)
onoremap <silent> IN" :call targets#o('"NI', v:count1)
onoremap <silent> Il" :call targets#o('"lI', v:count1)
onoremap <silent> In" :call targets#o('"nI', v:count1)
onoremap <silent> I" :call targets#o('"cI', v:count1)
onoremap <silent> Ilt :call targets#o('tlI', v:count1)
onoremap <silent> Int :call targets#o('tnI', v:count1)
onoremap <silent> It :call targets#o('tcI', v:count1)
onoremap <silent> Il> :call targets#o('>lI', v:count1)
onoremap <silent> In> :call targets#o('>nI', v:count1)
onoremap <silent> I> :call targets#o('>cI', v:count1)
onoremap <silent> Il< :call targets#o('<lI', v:count1)
onoremap <silent> In< :call targets#o('<nI', v:count1)
onoremap <silent> I< :call targets#o('<cI', v:count1)
onoremap <silent> Il] :call targets#o(']lI', v:count1)
onoremap <silent> In] :call targets#o(']nI', v:count1)
onoremap <silent> I] :call targets#o(']cI', v:count1)
onoremap <silent> Il[ :call targets#o('[lI', v:count1)
onoremap <silent> In[ :call targets#o('[nI', v:count1)
onoremap <silent> I[ :call targets#o('[cI', v:count1)
onoremap <silent> IlB :call targets#o('BlI', v:count1)
onoremap <silent> InB :call targets#o('BnI', v:count1)
onoremap <silent> IB :call targets#o('BcI', v:count1)
onoremap <silent> Il} :call targets#o('}lI', v:count1)
onoremap <silent> In} :call targets#o('}nI', v:count1)
onoremap <silent> I} :call targets#o('}cI', v:count1)
onoremap <silent> Il{ :call targets#o('{lI', v:count1)
onoremap <silent> In{ :call targets#o('{nI', v:count1)
onoremap <silent> I{ :call targets#o('{cI', v:count1)
onoremap <silent> Ilb :call targets#o('blI', v:count1)
onoremap <silent> Inb :call targets#o('bnI', v:count1)
onoremap <silent> Ib :call targets#o('bcI', v:count1)
onoremap <silent> Il) :call targets#o(')lI', v:count1)
onoremap <silent> In) :call targets#o(')nI', v:count1)
onoremap <silent> I) :call targets#o(')cI', v:count1)
onoremap <silent> Il( :call targets#o('(lI', v:count1)
onoremap <silent> In( :call targets#o('(nI', v:count1)
onoremap <silent> I( :call targets#o('(cI', v:count1)
xmap S <Plug>VSurround
nnoremap Y y$
nmap [xx <Plug>unimpaired_line_xml_encode
xmap [x <Plug>unimpaired_xml_encode
nmap [x <Plug>unimpaired_xml_encode
nmap [uu <Plug>unimpaired_line_url_encode
xmap [u <Plug>unimpaired_url_encode
nmap [u <Plug>unimpaired_url_encode
nmap [yy <Plug>unimpaired_line_string_encode
xmap [y <Plug>unimpaired_string_encode
nmap [y <Plug>unimpaired_string_encode
nmap [p <Plug>unimpairedPutAbove
nnoremap [ov :set virtualedit+=all
nnoremap [ox :set cursorline cursorcolumn
nnoremap [od :diffthis
nnoremap [ob :set background=light
xmap [e <Plug>unimpairedMoveSelectionUp
nmap [e <Plug>unimpairedMoveUp
nmap [  <Plug>unimpairedBlankUp
omap [n <Plug>unimpairedContextPrevious
nmap [n <Plug>unimpairedContextPrevious
nmap [o <Plug>unimpairedOPrevious
nmap [f <Plug>unimpairedDirectoryPrevious
nmap <silent> [T <Plug>unimpairedTFirst
nmap <silent> [t <Plug>unimpairedTPrevious
nmap <silent> [ <Plug>unimpairedQPFile
nmap <silent> [Q <Plug>unimpairedQFirst
nmap <silent> [q <Plug>unimpairedQPrevious
nmap <silent> [ <Plug>unimpairedLPFile
nmap <silent> [L <Plug>unimpairedLFirst
nmap <silent> [l <Plug>unimpairedLPrevious
nmap <silent> [B <Plug>unimpairedBFirst
nmap <silent> [b <Plug>unimpairedBPrevious
nmap <silent> [A <Plug>unimpairedAFirst
nmap <silent> [a <Plug>unimpairedAPrevious
xmap [, <Plug>Argumentative_XPrev
omap [, <Plug>Argumentative_Prev
nmap [, <Plug>Argumentative_Prev
vmap [% [%m'gv``
nmap \* :execute 'noautocmd vimgrep /\V' . substitute(escape(expand("<cword>"), '\'), '\n', '\\n', 'g') . '/ **'
xnoremap \pe :!python 
xnoremap \bc :!bc -l
nnoremap \w :w
nnoremap \V :sp
nnoremap \v :vs
nnoremap \T :!ctags -R
nnoremap \tr :%s/\s*$//gzz
nnoremap \tn :tabnew
nnoremap \scm :!racket -r %
nnoremap \sap vip:sort
nnoremap \rs :!Rscript %
nnoremap \rl :so ~/.vim/vimrc
nnoremap \rh :!runhaskell %
nnoremap \rb :!ruby %
nnoremap \q :q!
nnoremap \py :!python %
nnoremap \pl :!perl %
nnoremap \pi :PlugInstall
nnoremap \pfc \pt"*p\pt
nnoremap \p3 :!python3 %
nnoremap \p2 :!python2 %
nmap \O <Plug>(altr-forward)
nnoremap \o :BLines
nnoremap \mt :make tests
nnoremap \me :au BufWritePost * make
nnoremap <silent> \n :nohlsearch
nnoremap \i :e ~/.vim/vimrc
nnoremap \gpp :!g++ -g -std=c++11 % -o %< && ./%<
nnoremap \gcc :!gcc -g -std=c99 % -o %< && ./%<
noremap \G :Google
nnoremap \g :Gstatus
nnoremap \F :Files ~/
nnoremap \f :Files
nnoremap \d :cd %:p:h
nnoremap \C :BCommits
nnoremap \c :make
nnoremap \b :Buffers
nnoremap \asc ggVG:Tab /;
nnoremap <silent> \. :Ag 
nnoremap <silent> \/ :Ag 
nmap ]xx <Plug>unimpaired_line_xml_decode
xmap ]x <Plug>unimpaired_xml_decode
nmap ]x <Plug>unimpaired_xml_decode
nmap ]uu <Plug>unimpaired_line_url_decode
xmap ]u <Plug>unimpaired_url_decode
nmap ]u <Plug>unimpaired_url_decode
nmap ]yy <Plug>unimpaired_line_string_decode
xmap ]y <Plug>unimpaired_string_decode
nmap ]y <Plug>unimpaired_string_decode
nmap ]p <Plug>unimpairedPutBelow
nnoremap ]ov :set virtualedit-=all
nnoremap ]ox :set nocursorline nocursorcolumn
nnoremap ]od :diffoff
nnoremap ]ob :set background=dark
xmap ]e <Plug>unimpairedMoveSelectionDown
nmap ]e <Plug>unimpairedMoveDown
nmap ]  <Plug>unimpairedBlankDown
omap ]n <Plug>unimpairedContextNext
nmap ]n <Plug>unimpairedContextNext
nmap ]o <Plug>unimpairedONext
nmap ]f <Plug>unimpairedDirectoryNext
nmap <silent> ]T <Plug>unimpairedTLast
nmap <silent> ]t <Plug>unimpairedTNext
nmap <silent> ] <Plug>unimpairedQNFile
nmap <silent> ]Q <Plug>unimpairedQLast
nmap <silent> ]q <Plug>unimpairedQNext
nmap <silent> ] <Plug>unimpairedLNFile
nmap <silent> ]L <Plug>unimpairedLLast
nmap <silent> ]l <Plug>unimpairedLNext
nmap <silent> ]B <Plug>unimpairedBLast
nmap <silent> ]b <Plug>unimpairedBNext
nmap <silent> ]A <Plug>unimpairedALast
nmap <silent> ]a <Plug>unimpairedANext
xmap ], <Plug>Argumentative_XNext
omap ], <Plug>Argumentative_Next
nmap ], <Plug>Argumentative_Next
vmap ]% ]%m'gv``
nnoremap ` '
omap ae <Plug>(textobj-entire-a)
xmap ae <Plug>(textobj-entire-a)
xmap a, <Plug>Argumentative_OuterTextObject
xnoremap <silent> <expr> a targets#e('a')
onoremap <silent> ala :call targets#o('ala', v:count1)
onoremap <silent> ana :call targets#o('ana', v:count1)
onoremap <silent> aa :call targets#o('aca', v:count1)
onoremap <silent> aL$ :call targets#o('$La', v:count1)
onoremap <silent> aN$ :call targets#o('$Na', v:count1)
onoremap <silent> al$ :call targets#o('$la', v:count1)
onoremap <silent> an$ :call targets#o('$na', v:count1)
onoremap <silent> a$ :call targets#o('$ca', v:count1)
onoremap <silent> aL& :call targets#o('&La', v:count1)
onoremap <silent> aN& :call targets#o('&Na', v:count1)
onoremap <silent> al& :call targets#o('&la', v:count1)
onoremap <silent> an& :call targets#o('&na', v:count1)
onoremap <silent> a& :call targets#o('&ca', v:count1)
onoremap <silent> aL| :call targets#o('|La', v:count1)
onoremap <silent> aN| :call targets#o('|Na', v:count1)
onoremap <silent> al| :call targets#o('|la', v:count1)
onoremap <silent> an| :call targets#o('|na', v:count1)
onoremap <silent> a| :call targets#o('|ca', v:count1)
onoremap <silent> aL\ :call targets#o('\La', v:count1)
onoremap <silent> aN\ :call targets#o('\Na', v:count1)
onoremap <silent> al\ :call targets#o('\la', v:count1)
onoremap <silent> an\ :call targets#o('\na', v:count1)
onoremap <silent> a\ :call targets#o('\ca', v:count1)
onoremap <silent> aL/ :call targets#o('/La', v:count1)
onoremap <silent> aN/ :call targets#o('/Na', v:count1)
onoremap <silent> al/ :call targets#o('/la', v:count1)
onoremap <silent> an/ :call targets#o('/na', v:count1)
onoremap <silent> a/ :call targets#o('/ca', v:count1)
onoremap <silent> aL# :call targets#o('#La', v:count1)
onoremap <silent> aN# :call targets#o('#Na', v:count1)
onoremap <silent> al# :call targets#o('#la', v:count1)
onoremap <silent> an# :call targets#o('#na', v:count1)
onoremap <silent> a# :call targets#o('#ca', v:count1)
onoremap <silent> aL* :call targets#o('*La', v:count1)
onoremap <silent> aN* :call targets#o('*Na', v:count1)
onoremap <silent> al* :call targets#o('*la', v:count1)
onoremap <silent> an* :call targets#o('*na', v:count1)
onoremap <silent> a* :call targets#o('*ca', v:count1)
onoremap <silent> aL_ :call targets#o('_La', v:count1)
onoremap <silent> aN_ :call targets#o('_Na', v:count1)
onoremap <silent> al_ :call targets#o('_la', v:count1)
onoremap <silent> an_ :call targets#o('_na', v:count1)
onoremap <silent> a_ :call targets#o('_ca', v:count1)
onoremap <silent> aL~ :call targets#o('~La', v:count1)
onoremap <silent> aN~ :call targets#o('~Na', v:count1)
onoremap <silent> al~ :call targets#o('~la', v:count1)
onoremap <silent> an~ :call targets#o('~na', v:count1)
onoremap <silent> a~ :call targets#o('~ca', v:count1)
onoremap <silent> aL= :call targets#o('=La', v:count1)
onoremap <silent> aN= :call targets#o('=Na', v:count1)
onoremap <silent> al= :call targets#o('=la', v:count1)
onoremap <silent> an= :call targets#o('=na', v:count1)
onoremap <silent> a= :call targets#o('=ca', v:count1)
onoremap <silent> aL- :call targets#o('-La', v:count1)
onoremap <silent> aN- :call targets#o('-Na', v:count1)
onoremap <silent> al- :call targets#o('-la', v:count1)
onoremap <silent> an- :call targets#o('-na', v:count1)
onoremap <silent> a- :call targets#o('-ca', v:count1)
onoremap <silent> aL+ :call targets#o('+La', v:count1)
onoremap <silent> aN+ :call targets#o('+Na', v:count1)
onoremap <silent> al+ :call targets#o('+la', v:count1)
onoremap <silent> an+ :call targets#o('+na', v:count1)
onoremap <silent> a+ :call targets#o('+ca', v:count1)
onoremap <silent> aL: :call targets#o(':La', v:count1)
onoremap <silent> aN: :call targets#o(':Na', v:count1)
onoremap <silent> al: :call targets#o(':la', v:count1)
onoremap <silent> an: :call targets#o(':na', v:count1)
onoremap <silent> a: :call targets#o(':ca', v:count1)
onoremap <silent> aL; :call targets#o(';La', v:count1)
onoremap <silent> aN; :call targets#o(';Na', v:count1)
onoremap <silent> al; :call targets#o(';la', v:count1)
onoremap <silent> an; :call targets#o(';na', v:count1)
onoremap <silent> a; :call targets#o(';ca', v:count1)
onoremap <silent> aL. :call targets#o('.La', v:count1)
onoremap <silent> aN. :call targets#o('.Na', v:count1)
onoremap <silent> al. :call targets#o('.la', v:count1)
onoremap <silent> an. :call targets#o('.na', v:count1)
onoremap <silent> a. :call targets#o('.ca', v:count1)
onoremap <silent> aL, :call targets#o(',La', v:count1)
onoremap <silent> aN, :call targets#o(',Na', v:count1)
onoremap <silent> al, :call targets#o(',la', v:count1)
onoremap <silent> an, :call targets#o(',na', v:count1)
omap a, <Plug>Argumentative_OpPendingOuterTextObject
onoremap <silent> aL` :call targets#o('`La', v:count1)
onoremap <silent> aN` :call targets#o('`Na', v:count1)
onoremap <silent> al` :call targets#o('`la', v:count1)
onoremap <silent> an` :call targets#o('`na', v:count1)
onoremap <silent> a` :call targets#o('`ca', v:count1)
onoremap <silent> aL' :call targets#o('''La', v:count1)
onoremap <silent> aN' :call targets#o('''Na', v:count1)
onoremap <silent> al' :call targets#o('''la', v:count1)
onoremap <silent> an' :call targets#o('''na', v:count1)
onoremap <silent> a' :call targets#o('''ca', v:count1)
onoremap <silent> aL" :call targets#o('"La', v:count1)
onoremap <silent> aN" :call targets#o('"Na', v:count1)
onoremap <silent> al" :call targets#o('"la', v:count1)
onoremap <silent> an" :call targets#o('"na', v:count1)
onoremap <silent> a" :call targets#o('"ca', v:count1)
onoremap <silent> alt :call targets#o('tla', v:count1)
onoremap <silent> ant :call targets#o('tna', v:count1)
onoremap <silent> at :call targets#o('tca', v:count1)
onoremap <silent> al> :call targets#o('>la', v:count1)
onoremap <silent> an> :call targets#o('>na', v:count1)
onoremap <silent> a> :call targets#o('>ca', v:count1)
onoremap <silent> al< :call targets#o('<la', v:count1)
onoremap <silent> an< :call targets#o('<na', v:count1)
onoremap <silent> a< :call targets#o('<ca', v:count1)
onoremap <silent> al] :call targets#o(']la', v:count1)
onoremap <silent> an] :call targets#o(']na', v:count1)
onoremap <silent> a] :call targets#o(']ca', v:count1)
onoremap <silent> al[ :call targets#o('[la', v:count1)
onoremap <silent> an[ :call targets#o('[na', v:count1)
onoremap <silent> a[ :call targets#o('[ca', v:count1)
onoremap <silent> alB :call targets#o('Bla', v:count1)
onoremap <silent> anB :call targets#o('Bna', v:count1)
onoremap <silent> aB :call targets#o('Bca', v:count1)
onoremap <silent> al} :call targets#o('}la', v:count1)
onoremap <silent> an} :call targets#o('}na', v:count1)
onoremap <silent> a} :call targets#o('}ca', v:count1)
onoremap <silent> al{ :call targets#o('{la', v:count1)
onoremap <silent> an{ :call targets#o('{na', v:count1)
onoremap <silent> a{ :call targets#o('{ca', v:count1)
onoremap <silent> alb :call targets#o('bla', v:count1)
onoremap <silent> anb :call targets#o('bna', v:count1)
onoremap <silent> ab :call targets#o('bca', v:count1)
onoremap <silent> al) :call targets#o(')la', v:count1)
onoremap <silent> an) :call targets#o(')na', v:count1)
onoremap <silent> a) :call targets#o(')ca', v:count1)
onoremap <silent> al( :call targets#o('(la', v:count1)
onoremap <silent> an( :call targets#o('(na', v:count1)
onoremap <silent> a( :call targets#o('(ca', v:count1)
vmap a% [%v]%
nnoremap cov :set =(&virtualedit =~# "all") ? 'virtualedit-=all' : 'virtualedit+=all'
nnoremap cox :set =&cursorline && &cursorcolumn ? 'nocursorline nocursorcolumn' : 'cursorline cursorcolumn'
nnoremap cod :=&diff ? 'diffoff' : 'diffthis'
nnoremap cob :set background==&background == 'dark' ? 'light' : 'dark'
nmap cS <Plug>CSurround
nmap cs <Plug>Csurround
nmap cgc <Plug>ChangeCommentary
nmap cr <Plug>Coerce
nmap ds <Plug>Dsurround
nnoremap <silent> dsa ds}dF\
vmap gx <Plug>NetrwBrowseXVis
nmap gx <Plug>NetrwBrowseX
xmap gS <Plug>VgSurround
nmap gcu <Plug>Commentary<Plug>Commentary
nmap gcc <Plug>CommentaryLine
omap gc <Plug>Commentary
nmap gc <Plug>Commentary
xmap gc <Plug>Commentary
vmap <silent> gL <Plug>VLionLeft
nmap <silent> gL <Plug>LionLeft
vmap <silent> gl <Plug>VLionRight
nmap <silent> gl <Plug>LionRight
nnoremap gK :!cppman 
omap ie <Plug>(textobj-entire-i)
xmap ie <Plug>(textobj-entire-i)
xmap i, <Plug>Argumentative_InnerTextObject
xnoremap <silent> <expr> i targets#e('i')
onoremap <silent> ila :call targets#o('ali', v:count1)
onoremap <silent> ina :call targets#o('ani', v:count1)
onoremap <silent> ia :call targets#o('aci', v:count1)
onoremap <silent> iL$ :call targets#o('$Li', v:count1)
onoremap <silent> iN$ :call targets#o('$Ni', v:count1)
onoremap <silent> il$ :call targets#o('$li', v:count1)
onoremap <silent> in$ :call targets#o('$ni', v:count1)
onoremap <silent> i$ :call targets#o('$ci', v:count1)
onoremap <silent> iL& :call targets#o('&Li', v:count1)
onoremap <silent> iN& :call targets#o('&Ni', v:count1)
onoremap <silent> il& :call targets#o('&li', v:count1)
onoremap <silent> in& :call targets#o('&ni', v:count1)
onoremap <silent> i& :call targets#o('&ci', v:count1)
onoremap <silent> iL| :call targets#o('|Li', v:count1)
onoremap <silent> iN| :call targets#o('|Ni', v:count1)
onoremap <silent> il| :call targets#o('|li', v:count1)
onoremap <silent> in| :call targets#o('|ni', v:count1)
onoremap <silent> i| :call targets#o('|ci', v:count1)
onoremap <silent> iL\ :call targets#o('\Li', v:count1)
onoremap <silent> iN\ :call targets#o('\Ni', v:count1)
onoremap <silent> il\ :call targets#o('\li', v:count1)
onoremap <silent> in\ :call targets#o('\ni', v:count1)
onoremap <silent> i\ :call targets#o('\ci', v:count1)
onoremap <silent> iL/ :call targets#o('/Li', v:count1)
onoremap <silent> iN/ :call targets#o('/Ni', v:count1)
onoremap <silent> il/ :call targets#o('/li', v:count1)
onoremap <silent> in/ :call targets#o('/ni', v:count1)
onoremap <silent> i/ :call targets#o('/ci', v:count1)
onoremap <silent> iL# :call targets#o('#Li', v:count1)
onoremap <silent> iN# :call targets#o('#Ni', v:count1)
onoremap <silent> il# :call targets#o('#li', v:count1)
onoremap <silent> in# :call targets#o('#ni', v:count1)
onoremap <silent> i# :call targets#o('#ci', v:count1)
onoremap <silent> iL* :call targets#o('*Li', v:count1)
onoremap <silent> iN* :call targets#o('*Ni', v:count1)
onoremap <silent> il* :call targets#o('*li', v:count1)
onoremap <silent> in* :call targets#o('*ni', v:count1)
onoremap <silent> i* :call targets#o('*ci', v:count1)
onoremap <silent> iL_ :call targets#o('_Li', v:count1)
onoremap <silent> iN_ :call targets#o('_Ni', v:count1)
onoremap <silent> il_ :call targets#o('_li', v:count1)
onoremap <silent> in_ :call targets#o('_ni', v:count1)
onoremap <silent> i_ :call targets#o('_ci', v:count1)
onoremap <silent> iL~ :call targets#o('~Li', v:count1)
onoremap <silent> iN~ :call targets#o('~Ni', v:count1)
onoremap <silent> il~ :call targets#o('~li', v:count1)
onoremap <silent> in~ :call targets#o('~ni', v:count1)
onoremap <silent> i~ :call targets#o('~ci', v:count1)
onoremap <silent> iL= :call targets#o('=Li', v:count1)
onoremap <silent> iN= :call targets#o('=Ni', v:count1)
onoremap <silent> il= :call targets#o('=li', v:count1)
onoremap <silent> in= :call targets#o('=ni', v:count1)
onoremap <silent> i= :call targets#o('=ci', v:count1)
onoremap <silent> iL- :call targets#o('-Li', v:count1)
onoremap <silent> iN- :call targets#o('-Ni', v:count1)
onoremap <silent> il- :call targets#o('-li', v:count1)
onoremap <silent> in- :call targets#o('-ni', v:count1)
onoremap <silent> i- :call targets#o('-ci', v:count1)
onoremap <silent> iL+ :call targets#o('+Li', v:count1)
onoremap <silent> iN+ :call targets#o('+Ni', v:count1)
onoremap <silent> il+ :call targets#o('+li', v:count1)
onoremap <silent> in+ :call targets#o('+ni', v:count1)
onoremap <silent> i+ :call targets#o('+ci', v:count1)
onoremap <silent> iL: :call targets#o(':Li', v:count1)
onoremap <silent> iN: :call targets#o(':Ni', v:count1)
onoremap <silent> il: :call targets#o(':li', v:count1)
onoremap <silent> in: :call targets#o(':ni', v:count1)
onoremap <silent> i: :call targets#o(':ci', v:count1)
onoremap <silent> iL; :call targets#o(';Li', v:count1)
onoremap <silent> iN; :call targets#o(';Ni', v:count1)
onoremap <silent> il; :call targets#o(';li', v:count1)
onoremap <silent> in; :call targets#o(';ni', v:count1)
onoremap <silent> i; :call targets#o(';ci', v:count1)
onoremap <silent> iL. :call targets#o('.Li', v:count1)
onoremap <silent> iN. :call targets#o('.Ni', v:count1)
onoremap <silent> il. :call targets#o('.li', v:count1)
onoremap <silent> in. :call targets#o('.ni', v:count1)
onoremap <silent> i. :call targets#o('.ci', v:count1)
onoremap <silent> iL, :call targets#o(',Li', v:count1)
onoremap <silent> iN, :call targets#o(',Ni', v:count1)
onoremap <silent> il, :call targets#o(',li', v:count1)
onoremap <silent> in, :call targets#o(',ni', v:count1)
omap i, <Plug>Argumentative_OpPendingInnerTextObject
onoremap <silent> iL` :call targets#o('`Li', v:count1)
onoremap <silent> iN` :call targets#o('`Ni', v:count1)
onoremap <silent> il` :call targets#o('`li', v:count1)
onoremap <silent> in` :call targets#o('`ni', v:count1)
onoremap <silent> i` :call targets#o('`ci', v:count1)
onoremap <silent> iL' :call targets#o('''Li', v:count1)
onoremap <silent> iN' :call targets#o('''Ni', v:count1)
onoremap <silent> il' :call targets#o('''li', v:count1)
onoremap <silent> in' :call targets#o('''ni', v:count1)
onoremap <silent> i' :call targets#o('''ci', v:count1)
onoremap <silent> iL" :call targets#o('"Li', v:count1)
onoremap <silent> iN" :call targets#o('"Ni', v:count1)
onoremap <silent> il" :call targets#o('"li', v:count1)
onoremap <silent> in" :call targets#o('"ni', v:count1)
onoremap <silent> i" :call targets#o('"ci', v:count1)
onoremap <silent> ilt :call targets#o('tli', v:count1)
onoremap <silent> int :call targets#o('tni', v:count1)
onoremap <silent> it :call targets#o('tci', v:count1)
onoremap <silent> il> :call targets#o('>li', v:count1)
onoremap <silent> in> :call targets#o('>ni', v:count1)
onoremap <silent> i> :call targets#o('>ci', v:count1)
onoremap <silent> il< :call targets#o('<li', v:count1)
onoremap <silent> in< :call targets#o('<ni', v:count1)
onoremap <silent> i< :call targets#o('<ci', v:count1)
onoremap <silent> il] :call targets#o(']li', v:count1)
onoremap <silent> in] :call targets#o(']ni', v:count1)
onoremap <silent> i] :call targets#o(']ci', v:count1)
onoremap <silent> il[ :call targets#o('[li', v:count1)
onoremap <silent> in[ :call targets#o('[ni', v:count1)
onoremap <silent> i[ :call targets#o('[ci', v:count1)
onoremap <silent> ilB :call targets#o('Bli', v:count1)
onoremap <silent> inB :call targets#o('Bni', v:count1)
onoremap <silent> iB :call targets#o('Bci', v:count1)
onoremap <silent> il} :call targets#o('}li', v:count1)
onoremap <silent> in} :call targets#o('}ni', v:count1)
onoremap <silent> i} :call targets#o('}ci', v:count1)
onoremap <silent> il{ :call targets#o('{li', v:count1)
onoremap <silent> in{ :call targets#o('{ni', v:count1)
onoremap <silent> i{ :call targets#o('{ci', v:count1)
onoremap <silent> ilb :call targets#o('bli', v:count1)
onoremap <silent> inb :call targets#o('bni', v:count1)
onoremap <silent> ib :call targets#o('bci', v:count1)
onoremap <silent> il) :call targets#o(')li', v:count1)
onoremap <silent> in) :call targets#o(')ni', v:count1)
onoremap <silent> i) :call targets#o(')ci', v:count1)
onoremap <silent> il( :call targets#o('(li', v:count1)
onoremap <silent> in( :call targets#o('(ni', v:count1)
onoremap <silent> i( :call targets#o('(ci', v:count1)
nnoremap <silent> j :execute 'normal!' (v:count > 1 ? "m'" . v:count : '') . 'j'
nnoremap <silent> k :execute 'normal!' (v:count > 1 ? "m'" . v:count : '') . 'k'
nmap ySS <Plug>YSsurround
nmap ySs <Plug>YSsurround
nmap yss <Plug>Yssurround
nmap yS <Plug>YSurround
nmap ys <Plug>Ysurround
noremap <Plug>(-fzf-vim-dq) "
nnoremap <Plug>(-fzf-vim-do) :execute g:__fzf_command
vnoremap <silent> <Plug>NetrwBrowseXVis :call netrw#BrowseXVis()
nnoremap <silent> <Plug>NetrwBrowseX :call netrw#BrowseX(expand((exists("g:netrw_gx")? g:netrw_gx : '<cfile>')),netrw#CheckIfRemote())
onoremap <silent> <Plug>(textobj-entire-i) :call g:__textobj_entire.do_by_function("select-i","-","o")
vnoremap <silent> <Plug>(textobj-entire-i) :call g:__textobj_entire.do_by_function("select-i","-","v")
onoremap <silent> <Plug>(textobj-entire-a) :call g:__textobj_entire.do_by_function("select-a","-","o")
vnoremap <silent> <Plug>(textobj-entire-a) :call g:__textobj_entire.do_by_function("select-a","-","v")
nmap <silent> <Plug>unimpairedOPrevious <Plug>unimpairedDirectoryPrevious:echohl WarningMSG|echo "[o is deprecated. Use [f"|echohl NONE
nmap <silent> <Plug>unimpairedONext <Plug>unimpairedDirectoryNext:echohl WarningMSG|echo "]o is deprecated. Use ]f"|echohl NONE
nnoremap <silent> <Plug>unimpairedTLast :exe "".(v:count ? v:count : "")."tlast"
nnoremap <silent> <Plug>unimpairedTFirst :exe "".(v:count ? v:count : "")."tfirst"
nnoremap <silent> <Plug>unimpairedTNext :exe "".(v:count ? v:count : "")."tnext"
nnoremap <silent> <Plug>unimpairedTPrevious :exe "".(v:count ? v:count : "")."tprevious"
nnoremap <silent> <Plug>unimpairedQNFile :exe "".(v:count ? v:count : "")."cnfile"zv
nnoremap <silent> <Plug>unimpairedQPFile :exe "".(v:count ? v:count : "")."cpfile"zv
nnoremap <silent> <Plug>unimpairedQLast :exe "".(v:count ? v:count : "")."clast"zv
nnoremap <silent> <Plug>unimpairedQFirst :exe "".(v:count ? v:count : "")."cfirst"zv
nnoremap <silent> <Plug>unimpairedQNext :exe "".(v:count ? v:count : "")."cnext"zv
nnoremap <silent> <Plug>unimpairedQPrevious :exe "".(v:count ? v:count : "")."cprevious"zv
nnoremap <silent> <Plug>unimpairedLNFile :exe "".(v:count ? v:count : "")."lnfile"zv
nnoremap <silent> <Plug>unimpairedLPFile :exe "".(v:count ? v:count : "")."lpfile"zv
nnoremap <silent> <Plug>unimpairedLLast :exe "".(v:count ? v:count : "")."llast"zv
nnoremap <silent> <Plug>unimpairedLFirst :exe "".(v:count ? v:count : "")."lfirst"zv
nnoremap <silent> <Plug>unimpairedLNext :exe "".(v:count ? v:count : "")."lnext"zv
nnoremap <silent> <Plug>unimpairedLPrevious :exe "".(v:count ? v:count : "")."lprevious"zv
nnoremap <silent> <Plug>unimpairedBLast :exe "".(v:count ? v:count : "")."blast"
nnoremap <silent> <Plug>unimpairedBFirst :exe "".(v:count ? v:count : "")."bfirst"
nnoremap <silent> <Plug>unimpairedBNext :exe "".(v:count ? v:count : "")."bnext"
nnoremap <silent> <Plug>unimpairedBPrevious :exe "".(v:count ? v:count : "")."bprevious"
nnoremap <silent> <Plug>unimpairedALast :exe "".(v:count ? v:count : "")."last"
nnoremap <silent> <Plug>unimpairedAFirst :exe "".(v:count ? v:count : "")."first"
nnoremap <silent> <Plug>unimpairedANext :exe "".(v:count ? v:count : "")."next"
nnoremap <silent> <Plug>unimpairedAPrevious :exe "".(v:count ? v:count : "")."previous"
nnoremap <silent> <Plug>SurroundRepeat .
nnoremap <SNR>31_: :=v:count ? v:count : ''
nmap <silent> <Plug>CommentaryUndo <Plug>Commentary<Plug>Commentary
nnoremap <silent> <Plug>LionRepeat .
vnoremap <silent> <Plug>(altr-forward) :call altr#forward()
onoremap <silent> <Plug>(altr-forward) :call altr#forward()
nnoremap <silent> <Plug>(altr-forward) :call altr#forward()
vnoremap <silent> <Plug>(altr-back) :call altr#back()
onoremap <silent> <Plug>(altr-back) :call altr#back()
nnoremap <silent> <Plug>(altr-back) :call altr#back()
snoremap <silent> <Del> c
snoremap <silent> <BS> c
snoremap <silent> <C-Tab> :call UltiSnips#ListSnippets()
nnoremap <Down> 5+
nnoremap <Up> 5-
nnoremap <Right> 5>
nnoremap <Left> 5<
imap S <Plug>ISurround
imap s <Plug>Isurround
inoremap  h
inoremap <silent> 	 =UltiSnips#ExpandSnippet()
inoremap <NL> j
inoremap  k
inoremap  l
imap  <Plug>Isurround
imap  <Plug>(fzf-complete-path)
inoremap  u[s1z=`]au
inoremap  {}O
inoremap jk 
let &cpo=s:cpo_save
unlet s:cpo_save
set autoindent
set background=dark
set backspace=indent,eol,start
set backup
set backupdir=~/.vimbak
set clipboard=unnamedplus
set completeopt=menu
set cryptmethod=blowfish2
set expandtab
set fileencodings=ucs-bom,utf-8,default,latin1
set gdefault
set helplang=en
set hidden
set history=10000
set hlsearch
set ignorecase
set incsearch
set pastetoggle=\\pt
set ruler
set runtimepath=~/.vim,~/.fzf/,~/.vim/plugged/fzf.vim/,~/.vim/plugged/gruvbox/,~/.vim/plugged/tabular/,~/.vim/plugged/targets.vim/,~/.vim/plugged/ultisnips/,~/.vim/plugged/vim-altr/,~/.vim/plugged/vim-argumentative/,~/.vim/plugged/vim-g/,~/.vim/plugged/vim-lion/,~/.vim/plugged/vim-abolish/,~/.vim/plugged/vim-commentary/,~/.vim/plugged/vim-fugitive/,~/.vim/plugged/vim-repeat/,~/.vim/plugged/vim-snippets/,~/.vim/plugged/vim-surround/,~/.vim/plugged/vim-unimpaired/,~/.vim/plugged/vim-textobj-user/,~/.vim/plugged/vim-textobj-entire/,~/.vim/plugged/vim-visual-increment/,~/.vim/plugged/vim-visual-star-search/,/usr/share/vim/vimfiles,/usr/share/vim/vim74,/usr/share/vim/vim74/pack/dist/opt/matchit,/usr/share/vim/vimfiles/after,~/.vim/plugged/tabular/after,~/.vim/plugged/ultisnips/after,~/.vim/after
set scrolloff=3
set shell=bash
set shiftwidth=4
set showcmd
set smartcase
set smarttab
set suffixes=.bak,~,.swp,.o,.info,.aux,.log,.dvi,.bbl,.blg,.brf,.cb,.ind,.idx,.ilg,.inx,.out,.toc,.png,.jpg
set noswapfile
set tabstop=4
set textwidth=79
set undodir=~/.vimundo
set undofile
set wildmenu
" vim: set ft=vim :
