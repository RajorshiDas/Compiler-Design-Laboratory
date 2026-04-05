param(
    [string]$Compiler = '.\compiler_report_check.exe'
)

$valid = Get-ChildItem $PSScriptRoot\t*.txt | Sort-Object Name

Write-Host "Running valid tests..."
foreach ($test in $valid) {
    Write-Host "`n=== $($test.Name) ==="
    if ($test.Name -eq 't03_io.txt') {
        "7" | & $Compiler $test.FullName
    } else {
        & $Compiler $test.FullName
    }
    Write-Host "ExitCode: $LASTEXITCODE"
}


