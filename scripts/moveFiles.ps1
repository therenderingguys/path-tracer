
$path=$args[0]
$tarfile=$args[1]
$zipFolderRoot=[System.IO.Path]::GetFileNameWithoutExtension(${tarfile})
$regexzipFolderRoot = Get-ChildItem $path | Where-Object { $_.Name.StartsWith($zipFolderRoot)}
$unpackedDir="${path}\${regexzipFolderRoot}"
#Write-Host "unpackedDir: $unpackedDir"

$immdDirName=(get-item $unpackedDir).Name
#Write-Host "immdDirName: $immdDirName"
if ( $immdDirName -eq (get-item $path).Name) {
    Write-Host "Rename: $unpackedDir to temp name"
    Rename-Item $unpackedDir "${immdDirName}_temp"
    $unpackedDir="${unpackedDir}_temp"
    #Write-Host "temp Path: $unpackedDir"
}
if (Test-Path $unpackedDir) {
    Write-Host "Moving Contents of: $unpackedDir"
    Move-Item -Path "${unpackedDir}\*" -Destination ${path}
    Remove-Item $unpackedDir
}


