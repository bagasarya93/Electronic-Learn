var gaugeTemp = new LinearGauge({
  renderTo: 'gaugetemperature',
  width: 160,
  height: 600,
  borderRadius: 20,
  borders: 0,
  barStrokeWidth: 20,
  minorTicks: 10,
  majorTicks: [0,10,20,30,40,50,60,70,80,90,100],
  value: 22.3,
  units: "Celcius",
}).draw();