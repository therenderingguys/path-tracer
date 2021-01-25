path=$1
tarfile=$2
zipName=$(basename -- "$tarfile")
zipFolderRoot=$(echo $zipName | rev | cut -f 2- -d '.' | rev)
regexzipFolderRoot=$(find $path -type d -mindepth 1 -maxdepth 1 -iname $zipFolderRoot*)

if [ ! -e "$regexzipFolderRoot" ]; then
    zipName=$(basename -- "$path")
    regexzipFolderRoot=$(find $path -type d -mindepth 1 -maxdepth 1 -iname $zipName)

fi
if [ -e "$regexzipFolderRoot" ]; then
    #cp -aR $regexzipFolderRoot/. $path &
    find $regexzipFolderRoot -mindepth 1 -maxdepth 1 -exec mv -t .. -- {} + &
    wait $!
    rm -rf $regexzipFolderRoot
fi