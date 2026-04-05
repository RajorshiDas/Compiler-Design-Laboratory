param(
    [string]$Compiler = '.\compiler_report_check.exe'
)

$valid = Get-ChildItem $PSScriptRoot\valid_*.txt | Sort-Object Name

Write-Host "Running valid tests..."
foreach ($test in $valid) {
    Write-Host "`n=== $($test.Name) ==="
    if ($test.Name -eq 'valid_03_read_write.txt') {
        "7" | & $Compiler $test.FullName
    } else {
        & $Compiler $test.FullName
    }
    Write-Host "ExitCode: $LASTEXITCODE"
}
