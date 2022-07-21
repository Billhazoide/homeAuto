/*
 * Uma empresa de segurança foi contratada para vigiar um longo muro. De acordo com o contrato, além de fazer o monitoramento através de câmeras e sensores, a empresa deve também fazer uma inspeção diária no muro, procurando por rachaduras, buracos e outras fragilidades estruturais. Por se tratar de uma tarefa delicada, são enviados guardas para percorrer a extensão do muro e detectar essas falhas. No entanto, como os guardas trabalham em turnos diferentes, a empresa suspeita que muitos guardas acabem passando pelo mesmo trecho do muro, o que indica que esse processo possa ser otimizado. Afim de verificar essa hipótese, a empresa pediu para que seus guardas registrassem o ponto inicial e final de suas patrulhas em uma planilha.

 Escreva uma função que, dados os pontos iniciais e finais da patrulha de dois guardas, determine se eles passaram por algum trecho do muro em comum. Considere que o objeto { start: a, end: b } represente a posição inicial (start) e final (end) de um guarda com relação à metade do muro. A função deve retornar `true` caso haja algum trecho em comum e `false` caso o contrário.
 */

function hasOverlap(interval1, interval2) {
  
  let intersection = false 
  if(interval1.end >= interval2.start || interval2.end >= interval1.end || interval2.start <= interval1.start) intersection = true 
  

  return intersection
}

// Funções para teste

let testCase = 0

const test = (interval1, interval2, expectedResult) => {
  const result = hasOverlap(interval1, interval2)
  if (result === expectedResult) {
    console.log(`${++testCase}. ${result} - ✓`)
  } else {
    console.log(`${++testCase}. ${result} - ✕ (expected ${expectedResult})`)
  }
}

test({ start: 0, end: 1 }, { start: 2, end: 3 }, false) // 1
test({ start: 1, end: 3 }, { start: 2, end: 4 }, true) // 2
test({ start: 2, end: 3 }, { start: 0, end: 1 }, false) // 3

test({ start: 2, end: 4 }, { start: 1, end: 3 }, true) // 4
test({ start: 4, end: 2 }, { start: 1, end: 3 }, true) // 5
test({ start: 1, end: 4 }, { start: 2, end: 3 }, true) // 6
test({ start: 2, end: 3 }, { start: 1, end: 4 }, true) // 7
test({ start: 1, end: 2 }, { start: 2, end: 3 }, true) // 8

test({ start: 1, end: 2 }, { start: 3, end: 2 }, true) // 9

test({ start: 1, end: 1 }, { start: 1, end: 1 }, true) // 10
test({ start: 3, end: 4 }, { start: 3.1, end: 3.2 }, true) // 11
test({ start: -2,  end: 3.14 }, { start: 2,  end: 4.2 }, true) // 12
