$ErrorActionPreference = 'Stop'
$destination = Join-Path $PSScriptRoot '../assets/audio'
[System.IO.Directory]::CreateDirectory($destination) | Out-Null
$sounds = @{
    pop = @(950, 0.07)
    buy = @(660, 0.15)
    win = @(880, 0.5)
    lose = @(160, 0.5)
}
foreach ($entry in $sounds.GetEnumerator()) {
    $rate = 22050
    $samples = [int]($rate * $entry.Value[1])
    $stream = [System.IO.File]::Create((Join-Path $destination ($entry.Key + '.wav')))
    $writer = [System.IO.BinaryWriter]::new($stream)
    $writer.Write([System.Text.Encoding]::ASCII.GetBytes('RIFF'))
    $writer.Write([int](36 + $samples * 2))
    $writer.Write([System.Text.Encoding]::ASCII.GetBytes('WAVEfmt '))
    $writer.Write([int]16)
    $writer.Write([int16]1)
    $writer.Write([int16]1)
    $writer.Write([int]$rate)
    $writer.Write([int]($rate * 2))
    $writer.Write([int16]2)
    $writer.Write([int16]16)
    $writer.Write([System.Text.Encoding]::ASCII.GetBytes('data'))
    $writer.Write([int]($samples * 2))
    for ($sample = 0; $sample -lt $samples; $sample++) {
        $time = $sample / $rate
        $envelope = [Math]::Sin([Math]::PI * $sample / $samples)
        $frequency = $entry.Value[0] * (1 + 0.15 * $sample / $samples)
        $writer.Write([int16](7000 * $envelope * [Math]::Sin(2 * [Math]::PI * $frequency * $time)))
    }
    $writer.Dispose()
}