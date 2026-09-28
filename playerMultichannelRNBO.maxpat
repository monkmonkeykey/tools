{
	"patcher" : 	{
		"fileversion" : 1,
		"appversion" : 		{
			"major" : 9,
			"minor" : 0,
			"revision" : 8,
			"architecture" : "x64",
			"modernui" : 1
		}
,
		"classnamespace" : "box",
		"rect" : [ 59.0, 119.0, 1000.0, 755.0 ],
		"gridsize" : [ 15.0, 15.0 ],
		"boxes" : [ 			{
				"box" : 				{
					"autosave" : 1,
					"id" : "obj-1",
					"inletInfo" : 					{
						"IOInfo" : [  ]
					}
,
					"linecount" : 2,
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 17,
					"outletInfo" : 					{
						"IOInfo" : [ 							{
								"type" : "signal",
								"index" : 1,
								"tag" : "out1",
								"comment" : ""
							}
, 							{
								"type" : "signal",
								"index" : 2,
								"tag" : "out2",
								"comment" : ""
							}
, 							{
								"type" : "signal",
								"index" : 3,
								"tag" : "out3",
								"comment" : ""
							}
, 							{
								"type" : "signal",
								"index" : 4,
								"tag" : "out4",
								"comment" : ""
							}
, 							{
								"type" : "signal",
								"index" : 5,
								"tag" : "out5",
								"comment" : ""
							}
, 							{
								"type" : "signal",
								"index" : 6,
								"tag" : "out6",
								"comment" : ""
							}
, 							{
								"type" : "signal",
								"index" : 7,
								"tag" : "out7",
								"comment" : ""
							}
, 							{
								"type" : "signal",
								"index" : 8,
								"tag" : "out8",
								"comment" : ""
							}
, 							{
								"type" : "signal",
								"index" : 9,
								"tag" : "out9",
								"comment" : ""
							}
, 							{
								"type" : "signal",
								"index" : 10,
								"tag" : "out10",
								"comment" : ""
							}
, 							{
								"type" : "signal",
								"index" : 11,
								"tag" : "out11",
								"comment" : ""
							}
, 							{
								"type" : "signal",
								"index" : 12,
								"tag" : "out12",
								"comment" : ""
							}
, 							{
								"type" : "signal",
								"index" : 13,
								"tag" : "out13",
								"comment" : ""
							}
, 							{
								"type" : "signal",
								"index" : 14,
								"tag" : "out14",
								"comment" : ""
							}
, 							{
								"type" : "signal",
								"index" : 15,
								"tag" : "out15",
								"comment" : ""
							}
, 							{
								"type" : "signal",
								"index" : 16,
								"tag" : "out16",
								"comment" : ""
							}
 ]
					}
,
					"outlettype" : [ "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "list" ],
					"patcher" : 					{
						"fileversion" : 1,
						"appversion" : 						{
							"major" : 9,
							"minor" : 0,
							"revision" : 8,
							"architecture" : "x64",
							"modernui" : 1
						}
,
						"classnamespace" : "rnbo",
						"rect" : [ 34.0, 100.0, 1043.0, 848.0 ],
						"default_fontname" : "Lato",
						"gridsize" : [ 15.0, 15.0 ],
						"title" : "untitled",
						"boxes" : [ 							{
								"box" : 								{
									"id" : "obj-170",
									"maxclass" : "newobj",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 801.298693656921387, 305.194802284240723, 67.0, 23.0 ],
									"rnbo_classname" : "delay",
									"rnbo_serial" : 1,
									"rnbo_uniqueid" : "delay_obj-170",
									"text" : "delay 2000"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-169",
									"maxclass" : "newobj",
									"numinlets" : 6,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 1716.504830837249756, 447.572809398174286, 103.0, 23.0 ],
									"rnbo_classname" : "scale",
									"rnbo_serial" : 1,
									"rnbo_uniqueid" : "scale_obj-169",
									"text" : "scale 0 135 0 100"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-168",
									"maxclass" : "newobj",
									"numinlets" : 6,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 1601.456288725137711, 447.572809398174286, 103.0, 23.0 ],
									"rnbo_classname" : "scale",
									"rnbo_serial" : 2,
									"rnbo_uniqueid" : "scale_obj-168",
									"text" : "scale 0 135 0 100"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-167",
									"maxclass" : "newobj",
									"numinlets" : 6,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 1483.495125293731689, 447.572809398174286, 103.0, 23.0 ],
									"rnbo_classname" : "scale",
									"rnbo_serial" : 3,
									"rnbo_uniqueid" : "scale_obj-167",
									"text" : "scale 0 135 0 100"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-166",
									"maxclass" : "newobj",
									"numinlets" : 6,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 1368.446583181619644, 447.572809398174286, 103.0, 23.0 ],
									"rnbo_classname" : "scale",
									"rnbo_serial" : 4,
									"rnbo_uniqueid" : "scale_obj-166",
									"text" : "scale 0 135 0 100"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-164",
									"maxclass" : "newobj",
									"numinlets" : 6,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 1253.398041069507599, 447.572809398174286, 103.0, 23.0 ],
									"rnbo_classname" : "scale",
									"rnbo_serial" : 5,
									"rnbo_uniqueid" : "scale_obj-164",
									"text" : "scale 0 135 0 100"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-165",
									"maxclass" : "newobj",
									"numinlets" : 6,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 1138.349498957395554, 447.572809398174286, 103.0, 23.0 ],
									"rnbo_classname" : "scale",
									"rnbo_serial" : 6,
									"rnbo_uniqueid" : "scale_obj-165",
									"text" : "scale 0 135 0 100"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-163",
									"maxclass" : "newobj",
									"numinlets" : 6,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 1020.388335525989532, 447.572809398174286, 103.0, 23.0 ],
									"rnbo_classname" : "scale",
									"rnbo_serial" : 7,
									"rnbo_uniqueid" : "scale_obj-163",
									"text" : "scale 0 135 0 100"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-162",
									"maxclass" : "newobj",
									"numinlets" : 6,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 905.339793413877487, 447.572809398174286, 103.0, 23.0 ],
									"rnbo_classname" : "scale",
									"rnbo_serial" : 8,
									"rnbo_uniqueid" : "scale_obj-162",
									"text" : "scale 0 135 0 100"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-161",
									"linecount" : 2,
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 3.883495092391968, 8.737863957881927, 102.42718306183815, 35.0 ],
									"text" : "Consultamos información"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-160",
									"linecount" : 4,
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 277.751856297254562, 14.285714149475098, 102.42718306183815, 64.0 ],
									"text" : "Al arrancar Obtenemos información del audio"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-156",
									"linecount" : 2,
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 801.456299692392349, 225.242715358734131, 150.0, 35.0 ],
									"text" : "Al iniciar establece el volumen al 50%"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-153",
									"maxclass" : "flonum",
									"maximum" : 135.0,
									"minimum" : 0.0,
									"numinlets" : 1,
									"numoutlets" : 2,
									"outlettype" : [ "", "bang" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 1716.504830837249756, 409.223295360803604, 50.0, 23.0 ],
									"rnbo_classname" : "number",
									"rnbo_extra_attributes" : 									{
										"maximum" : 135.0,
										"minimum" : 0.0,
										"initialFormat" : "float",
										"order" : "",
										"preset" : 0
									}
,
									"rnbo_serial" : 1,
									"rnbo_uniqueid" : "number_obj-153"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-151",
									"maxclass" : "flonum",
									"maximum" : 135.0,
									"minimum" : 0.0,
									"numinlets" : 1,
									"numoutlets" : 2,
									"outlettype" : [ "", "bang" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 1601.456288725137711, 409.223295360803604, 50.0, 23.0 ],
									"rnbo_classname" : "number",
									"rnbo_extra_attributes" : 									{
										"maximum" : 135.0,
										"minimum" : 0.0,
										"initialFormat" : "float",
										"order" : "",
										"preset" : 0
									}
,
									"rnbo_serial" : 2,
									"rnbo_uniqueid" : "number_obj-151"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-149",
									"maxclass" : "flonum",
									"maximum" : 135.0,
									"minimum" : 0.0,
									"numinlets" : 1,
									"numoutlets" : 2,
									"outlettype" : [ "", "bang" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 1483.495125293731689, 409.223295360803604, 50.0, 23.0 ],
									"rnbo_classname" : "number",
									"rnbo_extra_attributes" : 									{
										"maximum" : 135.0,
										"minimum" : 0.0,
										"initialFormat" : "float",
										"order" : "",
										"preset" : 0
									}
,
									"rnbo_serial" : 3,
									"rnbo_uniqueid" : "number_obj-149"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-148",
									"maxclass" : "flonum",
									"maximum" : 135.0,
									"minimum" : 0.0,
									"numinlets" : 1,
									"numoutlets" : 2,
									"outlettype" : [ "", "bang" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 1368.446583181619644, 409.223295360803604, 50.0, 23.0 ],
									"rnbo_classname" : "number",
									"rnbo_extra_attributes" : 									{
										"maximum" : 135.0,
										"minimum" : 0.0,
										"initialFormat" : "float",
										"order" : "",
										"preset" : 0
									}
,
									"rnbo_serial" : 4,
									"rnbo_uniqueid" : "number_obj-148"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-146",
									"maxclass" : "flonum",
									"maximum" : 135.0,
									"minimum" : 0.0,
									"numinlets" : 1,
									"numoutlets" : 2,
									"outlettype" : [ "", "bang" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 1253.398041069507599, 409.223295360803604, 50.0, 23.0 ],
									"rnbo_classname" : "number",
									"rnbo_extra_attributes" : 									{
										"maximum" : 135.0,
										"minimum" : 0.0,
										"initialFormat" : "float",
										"order" : "",
										"preset" : 0
									}
,
									"rnbo_serial" : 5,
									"rnbo_uniqueid" : "number_obj-146"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-144",
									"maxclass" : "flonum",
									"maximum" : 135.0,
									"minimum" : 0.0,
									"numinlets" : 1,
									"numoutlets" : 2,
									"outlettype" : [ "", "bang" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 1138.349498957395554, 409.223295360803604, 50.0, 23.0 ],
									"rnbo_classname" : "number",
									"rnbo_extra_attributes" : 									{
										"maximum" : 135.0,
										"minimum" : 0.0,
										"initialFormat" : "float",
										"order" : "",
										"preset" : 0
									}
,
									"rnbo_serial" : 6,
									"rnbo_uniqueid" : "number_obj-144"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-143",
									"maxclass" : "flonum",
									"maximum" : 135.0,
									"minimum" : 0.0,
									"numinlets" : 1,
									"numoutlets" : 2,
									"outlettype" : [ "", "bang" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 1020.388335525989532, 409.223295360803604, 50.0, 23.0 ],
									"rnbo_classname" : "number",
									"rnbo_extra_attributes" : 									{
										"maximum" : 135.0,
										"minimum" : 0.0,
										"initialFormat" : "float",
										"order" : "",
										"preset" : 0
									}
,
									"rnbo_serial" : 7,
									"rnbo_uniqueid" : "number_obj-143"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-136",
									"maxclass" : "flonum",
									"maximum" : 135.0,
									"minimum" : 0.0,
									"numinlets" : 1,
									"numoutlets" : 2,
									"outlettype" : [ "", "bang" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 905.339793413877487, 409.223295360803604, 50.0, 23.0 ],
									"rnbo_classname" : "number",
									"rnbo_extra_attributes" : 									{
										"maximum" : 135.0,
										"minimum" : 0.0,
										"initialFormat" : "float",
										"order" : "",
										"preset" : 0
									}
,
									"rnbo_serial" : 8,
									"rnbo_uniqueid" : "number_obj-136"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-131",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 801.456299692392349, 273.300967127084732, 56.0, 23.0 ],
									"rnbo_classname" : "loadbang",
									"rnbo_serial" : 1,
									"rnbo_uniqueid" : "loadbang_obj-131",
									"text" : "loadbang"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-130",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 801.456299692392349, 338.349509924650192, 29.5, 23.0 ],
									"rnbo_classname" : "message",
									"rnbo_extra_attributes" : 									{
										"text" : "",
										"storeempty" : 0
									}
,
									"rnbo_serial" : 1,
									"rnbo_uniqueid" : "message_obj-130",
									"text" : "0.5"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Lato",
									"fontsize" : 12.0,
									"id" : "obj-127",
									"maxclass" : "newobj",
									"numinlets" : 6,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 1716.504830837249756, 376.213587075471878, 94.0, 23.0 ],
									"rnbo_classname" : "scale",
									"rnbo_serial" : 9,
									"rnbo_uniqueid" : "foo[8]",
									"text" : "scale 0. 1. 0 135",
									"varname" : "foo[8]"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Lato",
									"fontsize" : 12.0,
									"id" : "obj-126",
									"maxclass" : "newobj",
									"numinlets" : 6,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 1601.456288725137711, 376.213587075471878, 94.0, 23.0 ],
									"rnbo_classname" : "scale",
									"rnbo_serial" : 10,
									"rnbo_uniqueid" : "foo[7]",
									"text" : "scale 0. 1. 0 135",
									"varname" : "foo[7]"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Lato",
									"fontsize" : 12.0,
									"id" : "obj-125",
									"maxclass" : "newobj",
									"numinlets" : 6,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 1483.495125293731689, 376.213587075471878, 94.0, 23.0 ],
									"rnbo_classname" : "scale",
									"rnbo_serial" : 11,
									"rnbo_uniqueid" : "foo[6]",
									"text" : "scale 0. 1. 0 135",
									"varname" : "foo[6]"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Lato",
									"fontsize" : 12.0,
									"id" : "obj-123",
									"maxclass" : "newobj",
									"numinlets" : 6,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 1368.446583181619644, 376.213587075471878, 94.0, 23.0 ],
									"rnbo_classname" : "scale",
									"rnbo_serial" : 12,
									"rnbo_uniqueid" : "foo[5]",
									"text" : "scale 0. 1. 0 135",
									"varname" : "foo[5]"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Lato",
									"fontsize" : 12.0,
									"id" : "obj-122",
									"maxclass" : "newobj",
									"numinlets" : 6,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 1253.398041069507599, 376.213587075471878, 94.0, 23.0 ],
									"rnbo_classname" : "scale",
									"rnbo_serial" : 13,
									"rnbo_uniqueid" : "foo[4]",
									"text" : "scale 0. 1. 0 135",
									"varname" : "foo[4]"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Lato",
									"fontsize" : 12.0,
									"id" : "obj-121",
									"maxclass" : "newobj",
									"numinlets" : 6,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 1138.349498957395554, 376.213587075471878, 94.0, 23.0 ],
									"rnbo_classname" : "scale",
									"rnbo_serial" : 14,
									"rnbo_uniqueid" : "foo[3]",
									"text" : "scale 0. 1. 0 135",
									"varname" : "foo[3]"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Lato",
									"fontsize" : 12.0,
									"id" : "obj-120",
									"maxclass" : "newobj",
									"numinlets" : 6,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 1020.388335525989532, 376.213587075471878, 94.0, 23.0 ],
									"rnbo_classname" : "scale",
									"rnbo_serial" : 15,
									"rnbo_uniqueid" : "foo[2]",
									"text" : "scale 0. 1. 0 135",
									"varname" : "foo[2]"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Lato",
									"fontsize" : 12.0,
									"id" : "obj-117",
									"maxclass" : "newobj",
									"numinlets" : 6,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 905.339793413877487, 376.213587075471878, 94.0, 23.0 ],
									"rnbo_classname" : "scale",
									"rnbo_serial" : 16,
									"rnbo_uniqueid" : "foo[1]",
									"text" : "scale 0. 1. 0 135",
									"varname" : "foo[1]"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-94",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 1716.504830837249756, 505.825235784053802, 103.0, 23.0 ],
									"rnbo_classname" : "outport",
									"rnbo_extra_attributes" : 									{
										"meta" : ""
									}
,
									"rnbo_serial" : 1,
									"rnbo_uniqueid" : "outport_obj-94",
									"text" : "outport volumen8"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-95",
									"maxclass" : "flonum",
									"numinlets" : 1,
									"numoutlets" : 2,
									"outlettype" : [ "", "bang" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 1716.504830837249756, 335.436888605356216, 50.0, 23.0 ],
									"rnbo_classname" : "number",
									"rnbo_extra_attributes" : 									{
										"maximum" : "<none>",
										"minimum" : "<none>",
										"initialFormat" : "float",
										"order" : "",
										"preset" : 0
									}
,
									"rnbo_serial" : 9,
									"rnbo_uniqueid" : "number_obj-95"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-96",
									"maxclass" : "newobj",
									"numinlets" : 0,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 1716.504830837249756, 273.300967127084732, 71.0, 23.0 ],
									"rnbo_classname" : "inport",
									"rnbo_extra_attributes" : 									{
										"meta" : ""
									}
,
									"rnbo_serial" : 1,
									"rnbo_uniqueid" : "inport_obj-96",
									"text" : "inport /vol8"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-98",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 1601.456288725137711, 505.825235784053802, 103.0, 23.0 ],
									"rnbo_classname" : "outport",
									"rnbo_extra_attributes" : 									{
										"meta" : ""
									}
,
									"rnbo_serial" : 2,
									"rnbo_uniqueid" : "outport_obj-98",
									"text" : "outport volumen7"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-99",
									"maxclass" : "flonum",
									"numinlets" : 1,
									"numoutlets" : 2,
									"outlettype" : [ "", "bang" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 1601.456288725137711, 335.436888605356216, 50.0, 23.0 ],
									"rnbo_classname" : "number",
									"rnbo_extra_attributes" : 									{
										"maximum" : "<none>",
										"minimum" : "<none>",
										"initialFormat" : "float",
										"order" : "",
										"preset" : 0
									}
,
									"rnbo_serial" : 10,
									"rnbo_uniqueid" : "number_obj-99"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-100",
									"maxclass" : "newobj",
									"numinlets" : 0,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 1601.456288725137711, 273.300967127084732, 71.0, 23.0 ],
									"rnbo_classname" : "inport",
									"rnbo_extra_attributes" : 									{
										"meta" : ""
									}
,
									"rnbo_serial" : 2,
									"rnbo_uniqueid" : "inport_obj-100",
									"text" : "inport /vol7"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-101",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 1483.495125293731689, 505.825235784053802, 103.0, 23.0 ],
									"rnbo_classname" : "outport",
									"rnbo_extra_attributes" : 									{
										"meta" : ""
									}
,
									"rnbo_serial" : 3,
									"rnbo_uniqueid" : "outport_obj-101",
									"text" : "outport volumen6"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-102",
									"maxclass" : "flonum",
									"numinlets" : 1,
									"numoutlets" : 2,
									"outlettype" : [ "", "bang" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 1483.495125293731689, 335.436888605356216, 50.0, 23.0 ],
									"rnbo_classname" : "number",
									"rnbo_extra_attributes" : 									{
										"maximum" : "<none>",
										"minimum" : "<none>",
										"initialFormat" : "float",
										"order" : "",
										"preset" : 0
									}
,
									"rnbo_serial" : 11,
									"rnbo_uniqueid" : "number_obj-102"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-105",
									"maxclass" : "newobj",
									"numinlets" : 0,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 1483.495125293731689, 273.300967127084732, 71.0, 23.0 ],
									"rnbo_classname" : "inport",
									"rnbo_extra_attributes" : 									{
										"meta" : ""
									}
,
									"rnbo_serial" : 3,
									"rnbo_uniqueid" : "inport_obj-105",
									"text" : "inport /vol6"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-106",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 1368.446583181619644, 505.825235784053802, 103.0, 23.0 ],
									"rnbo_classname" : "outport",
									"rnbo_extra_attributes" : 									{
										"meta" : ""
									}
,
									"rnbo_serial" : 4,
									"rnbo_uniqueid" : "outport_obj-106",
									"text" : "outport volumen5"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-107",
									"maxclass" : "flonum",
									"numinlets" : 1,
									"numoutlets" : 2,
									"outlettype" : [ "", "bang" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 1368.446583181619644, 335.436888605356216, 50.0, 23.0 ],
									"rnbo_classname" : "number",
									"rnbo_extra_attributes" : 									{
										"maximum" : "<none>",
										"minimum" : "<none>",
										"initialFormat" : "float",
										"order" : "",
										"preset" : 0
									}
,
									"rnbo_serial" : 12,
									"rnbo_uniqueid" : "number_obj-107"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-112",
									"maxclass" : "newobj",
									"numinlets" : 0,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 1368.446583181619644, 273.300967127084732, 71.0, 23.0 ],
									"rnbo_classname" : "inport",
									"rnbo_extra_attributes" : 									{
										"meta" : ""
									}
,
									"rnbo_serial" : 4,
									"rnbo_uniqueid" : "inport_obj-112",
									"text" : "inport /vol5"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-88",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 1253.398041069507599, 505.825235784053802, 103.0, 23.0 ],
									"rnbo_classname" : "outport",
									"rnbo_extra_attributes" : 									{
										"meta" : ""
									}
,
									"rnbo_serial" : 5,
									"rnbo_uniqueid" : "outport_obj-88",
									"text" : "outport volumen4"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-89",
									"maxclass" : "flonum",
									"numinlets" : 1,
									"numoutlets" : 2,
									"outlettype" : [ "", "bang" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 1253.398041069507599, 335.436888605356216, 50.0, 23.0 ],
									"rnbo_classname" : "number",
									"rnbo_extra_attributes" : 									{
										"maximum" : "<none>",
										"minimum" : "<none>",
										"initialFormat" : "float",
										"order" : "",
										"preset" : 0
									}
,
									"rnbo_serial" : 13,
									"rnbo_uniqueid" : "number_obj-89"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-90",
									"maxclass" : "newobj",
									"numinlets" : 0,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 1253.398041069507599, 273.300967127084732, 71.0, 23.0 ],
									"rnbo_classname" : "inport",
									"rnbo_extra_attributes" : 									{
										"meta" : ""
									}
,
									"rnbo_serial" : 5,
									"rnbo_uniqueid" : "inport_obj-90",
									"text" : "inport /vol4"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-91",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 1138.349498957395554, 505.825235784053802, 103.0, 23.0 ],
									"rnbo_classname" : "outport",
									"rnbo_extra_attributes" : 									{
										"meta" : ""
									}
,
									"rnbo_serial" : 6,
									"rnbo_uniqueid" : "outport_obj-91",
									"text" : "outport volumen3"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-92",
									"maxclass" : "flonum",
									"numinlets" : 1,
									"numoutlets" : 2,
									"outlettype" : [ "", "bang" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 1138.349498957395554, 335.436888605356216, 50.0, 23.0 ],
									"rnbo_classname" : "number",
									"rnbo_extra_attributes" : 									{
										"maximum" : "<none>",
										"minimum" : "<none>",
										"initialFormat" : "float",
										"order" : "",
										"preset" : 0
									}
,
									"rnbo_serial" : 14,
									"rnbo_uniqueid" : "number_obj-92"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-93",
									"maxclass" : "newobj",
									"numinlets" : 0,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 1138.349498957395554, 273.300967127084732, 71.0, 23.0 ],
									"rnbo_classname" : "inport",
									"rnbo_extra_attributes" : 									{
										"meta" : ""
									}
,
									"rnbo_serial" : 6,
									"rnbo_uniqueid" : "inport_obj-93",
									"text" : "inport /vol3"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-84",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 1020.388335525989532, 505.825235784053802, 103.0, 23.0 ],
									"rnbo_classname" : "outport",
									"rnbo_extra_attributes" : 									{
										"meta" : ""
									}
,
									"rnbo_serial" : 7,
									"rnbo_uniqueid" : "outport_obj-84",
									"text" : "outport volumen2"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-85",
									"maxclass" : "flonum",
									"numinlets" : 1,
									"numoutlets" : 2,
									"outlettype" : [ "", "bang" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 1020.388335525989532, 335.436888605356216, 50.0, 23.0 ],
									"rnbo_classname" : "number",
									"rnbo_extra_attributes" : 									{
										"maximum" : "<none>",
										"minimum" : "<none>",
										"initialFormat" : "float",
										"order" : "",
										"preset" : 0
									}
,
									"rnbo_serial" : 15,
									"rnbo_uniqueid" : "number_obj-85"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-86",
									"maxclass" : "newobj",
									"numinlets" : 0,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 1020.388335525989532, 273.300967127084732, 71.0, 23.0 ],
									"rnbo_classname" : "inport",
									"rnbo_extra_attributes" : 									{
										"meta" : ""
									}
,
									"rnbo_serial" : 7,
									"rnbo_uniqueid" : "inport_obj-86",
									"text" : "inport /vol2"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-61",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 905.339793413877487, 505.825235784053802, 103.0, 23.0 ],
									"rnbo_classname" : "outport",
									"rnbo_extra_attributes" : 									{
										"meta" : ""
									}
,
									"rnbo_serial" : 8,
									"rnbo_uniqueid" : "outport_obj-61",
									"text" : "outport volumen1"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-60",
									"maxclass" : "flonum",
									"numinlets" : 1,
									"numoutlets" : 2,
									"outlettype" : [ "", "bang" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 905.339793413877487, 335.436888605356216, 50.0, 23.0 ],
									"rnbo_classname" : "number",
									"rnbo_extra_attributes" : 									{
										"maximum" : "<none>",
										"minimum" : "<none>",
										"initialFormat" : "float",
										"order" : "",
										"preset" : 0
									}
,
									"rnbo_serial" : 16,
									"rnbo_uniqueid" : "number_obj-60"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-33",
									"maxclass" : "newobj",
									"numinlets" : 0,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 905.339793413877487, 273.300967127084732, 71.0, 23.0 ],
									"rnbo_classname" : "inport",
									"rnbo_extra_attributes" : 									{
										"meta" : ""
									}
,
									"rnbo_serial" : 8,
									"rnbo_uniqueid" : "inport_obj-33",
									"text" : "inport /vol1"
								}

							}
, 							{
								"box" : 								{
									"format" : 0,
									"id" : "obj-159",
									"maxclass" : "number",
									"numinlets" : 1,
									"numoutlets" : 2,
									"outlettype" : [ "", "bang" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 690.776689559221268, 339.320383697748184, 101.398602426052094, 23.0 ],
									"rnbo_classname" : "number",
									"rnbo_extra_attributes" : 									{
										"maximum" : "<none>",
										"minimum" : "<none>",
										"initialFormat" : "integer",
										"order" : "",
										"preset" : 0
									}
,
									"rnbo_serial" : 17,
									"rnbo_uniqueid" : "number_obj-159"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-157",
									"maxclass" : "newobj",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 690.776689559221268, 290.291258156299591, 31.0, 23.0 ],
									"rnbo_classname" : "/",
									"rnbo_extra_attributes" : 									{
										"hot" : 0
									}
,
									"rnbo_serial" : 1,
									"rnbo_uniqueid" : "/_obj-157",
									"text" : "/ 60"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-154",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 747.0873683989048, 505.825235784053802, 88.0, 23.0 ],
									"rnbo_classname" : "outport",
									"rnbo_extra_attributes" : 									{
										"meta" : ""
									}
,
									"rnbo_serial" : 9,
									"rnbo_uniqueid" : "outport_obj-154",
									"text" : "outport durSeg"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-152",
									"maxclass" : "flonum",
									"numinlets" : 1,
									"numoutlets" : 2,
									"outlettype" : [ "", "bang" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 652.427175521850586, 456.796110242605209, 50.0, 23.0 ],
									"rnbo_classname" : "number",
									"rnbo_extra_attributes" : 									{
										"maximum" : "<none>",
										"minimum" : "<none>",
										"initialFormat" : "float",
										"order" : "",
										"preset" : 0
									}
,
									"rnbo_serial" : 18,
									"rnbo_uniqueid" : "number_obj-152"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-150",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 652.427175521850586, 505.825235784053802, 69.0, 23.0 ],
									"rnbo_classname" : "outport",
									"rnbo_extra_attributes" : 									{
										"meta" : ""
									}
,
									"rnbo_serial" : 10,
									"rnbo_uniqueid" : "outport_obj-150",
									"text" : "outport seg"
								}

							}
, 							{
								"box" : 								{
									"fontface" : 0,
									"fontname" : "Lato",
									"fontsize" : 12.0,
									"id" : "obj-147",
									"interval" : 100.0,
									"maxclass" : "number~",
									"mode" : 2,
									"numinlets" : 2,
									"numoutlets" : 2,
									"outlettype" : [ "signal", "float" ],
									"patching_rect" : [ 616.019409030675888, 408.252421587705612, 56.0, 23.0 ],
									"rnbo_classname" : "number~",
									"rnbo_extra_attributes" : 									{
										"interval" : 100.0,
										"initialMode" : "monitor",
										"displaymode" : "first"
									}
,
									"rnbo_serial" : 1,
									"rnbo_uniqueid" : "number~_obj-147",
									"sig" : 0.0
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-141",
									"maxclass" : "newobj",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "signal" ],
									"patching_rect" : [ 616.99028280377388, 358.737859159708023, 54.0, 23.0 ],
									"rnbo_classname" : "*~",
									"rnbo_serial" : 1,
									"rnbo_uniqueid" : "*~_obj-141",
									"text" : "*~ 0.001"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-138",
									"maxclass" : "newobj",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 114.077668339014053, 102.42718306183815, 60.0, 23.0 ],
									"rnbo_classname" : "delay",
									"rnbo_serial" : 2,
									"rnbo_uniqueid" : "delay_obj-138",
									"text" : "delay 100"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-124",
									"maxclass" : "newobj",
									"numinlets" : 0,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 114.077668339014053, 8.737863957881927, 108.0, 23.0 ],
									"rnbo_classname" : "inport",
									"rnbo_extra_attributes" : 									{
										"meta" : ""
									}
,
									"rnbo_serial" : 9,
									"rnbo_uniqueid" : "inport_obj-124",
									"text" : "inport consultaInfo"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-118",
									"maxclass" : "button",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "bang" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 114.077668339014053, 64.077669024467468, 24.0, 24.0 ],
									"rnbo_classname" : "button",
									"rnbo_serial" : 2,
									"rnbo_uniqueid" : "button_obj-118"
								}

							}
, 							{
								"box" : 								{
									"format" : 0,
									"id" : "obj-113",
									"maxclass" : "number",
									"numinlets" : 1,
									"numoutlets" : 2,
									"outlettype" : [ "", "bang" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 469.959646672010422, 74.025973320007324, 50.0, 23.0 ],
									"rnbo_classname" : "number",
									"rnbo_extra_attributes" : 									{
										"maximum" : "<none>",
										"minimum" : "<none>",
										"initialFormat" : "integer",
										"order" : "",
										"preset" : 0
									}
,
									"rnbo_serial" : 19,
									"rnbo_uniqueid" : "number_obj-113"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-111",
									"maxclass" : "newobj",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 370.388344436883926, 177.18446359038353, 60.0, 23.0 ],
									"rnbo_classname" : "delay",
									"rnbo_serial" : 3,
									"rnbo_uniqueid" : "delay_obj-111",
									"text" : "delay 500"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-108",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 495.145624279975891, 283.495141744613647, 107.0, 23.0 ],
									"rnbo_classname" : "outport",
									"rnbo_extra_attributes" : 									{
										"meta" : ""
									}
,
									"rnbo_serial" : 11,
									"rnbo_uniqueid" : "outport_obj-108",
									"text" : "outport loopeando"
								}

							}
, 							{
								"box" : 								{
									"format" : 0,
									"id" : "obj-103",
									"maxclass" : "number",
									"numinlets" : 1,
									"numoutlets" : 2,
									"outlettype" : [ "", "bang" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 495.145624279975891, 245.631064593791962, 50.0, 23.0 ],
									"rnbo_classname" : "number",
									"rnbo_extra_attributes" : 									{
										"maximum" : "<none>",
										"minimum" : "<none>",
										"initialFormat" : "integer",
										"order" : "",
										"preset" : 0
									}
,
									"rnbo_serial" : 20,
									"rnbo_uniqueid" : "number_obj-103"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-97",
									"maxclass" : "newobj",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 264.764843434095383, 83.11688232421875, 60.0, 23.0 ],
									"rnbo_classname" : "delay",
									"rnbo_serial" : 4,
									"rnbo_uniqueid" : "delay_obj-97",
									"text" : "delay 250"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-75",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 521.359216153621674, 968.446588665246964, 50.0, 23.0 ],
									"rnbo_classname" : "out~",
									"rnbo_extra_attributes" : 									{
										"comment" : "",
										"meta" : ""
									}
,
									"rnbo_serial" : 1,
									"rnbo_uniqueid" : "out~_obj-75",
									"rnboinfo" : 									{
										"needsInstanceInfo" : 1,
										"argnames" : 										{
											"in1" : 											{
												"attrOrProp" : 1,
												"digest" : "signal sent to outlet with index 16",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 0,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"touched" : 0,
												"inlet" : 1,
												"type" : "signal"
											}
,
											"index" : 											{
												"attrOrProp" : 2,
												"digest" : "outlet number",
												"defaultarg" : 1,
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"touched" : 0,
												"type" : "number",
												"mandatory" : 1
											}
,
											"comment" : 											{
												"attrOrProp" : 2,
												"digest" : "mouse over comment",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"touched" : 0,
												"type" : "symbol"
											}
,
											"meta" : 											{
												"attrOrProp" : 2,
												"digest" : "A JSON formatted string containing metadata for use by the exported code",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"touched" : 0,
												"type" : "symbol",
												"defaultValue" : "",
												"label" : "Metadata",
												"displayorder" : 3
											}

										}
,
										"inputs" : [ 											{
												"name" : "in1",
												"type" : "signal",
												"digest" : "signal sent to outlet with index 16",
												"displayName" : "",
												"hot" : 1,
												"docked" : 0
											}
 ],
										"outputs" : [  ],
										"helpname" : "out~",
										"aliasOf" : "out~",
										"classname" : "out~",
										"operator" : 0,
										"versionId" : 1989326771,
										"changesPatcherIO" : 1
									}
,
									"text" : "out~ 16"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-77",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 499.999993145465851, 937.378627926111221, 50.0, 23.0 ],
									"rnbo_classname" : "out~",
									"rnbo_extra_attributes" : 									{
										"comment" : "",
										"meta" : ""
									}
,
									"rnbo_serial" : 2,
									"rnbo_uniqueid" : "out~_obj-77",
									"rnboinfo" : 									{
										"needsInstanceInfo" : 1,
										"argnames" : 										{
											"in1" : 											{
												"attrOrProp" : 1,
												"digest" : "signal sent to outlet with index 15",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 0,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"touched" : 0,
												"inlet" : 1,
												"type" : "signal"
											}
,
											"index" : 											{
												"attrOrProp" : 2,
												"digest" : "outlet number",
												"defaultarg" : 1,
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"touched" : 0,
												"type" : "number",
												"mandatory" : 1
											}
,
											"comment" : 											{
												"attrOrProp" : 2,
												"digest" : "mouse over comment",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"touched" : 0,
												"type" : "symbol"
											}
,
											"meta" : 											{
												"attrOrProp" : 2,
												"digest" : "A JSON formatted string containing metadata for use by the exported code",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"touched" : 0,
												"type" : "symbol",
												"defaultValue" : "",
												"label" : "Metadata",
												"displayorder" : 3
											}

										}
,
										"inputs" : [ 											{
												"name" : "in1",
												"type" : "signal",
												"digest" : "signal sent to outlet with index 15",
												"displayName" : "",
												"hot" : 1,
												"docked" : 0
											}
 ],
										"outputs" : [  ],
										"helpname" : "out~",
										"aliasOf" : "out~",
										"classname" : "out~",
										"operator" : 0,
										"versionId" : 1989326771,
										"changesPatcherIO" : 1
									}
,
									"text" : "out~ 15"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-78",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 477.669896364212036, 907.281540960073471, 50.0, 23.0 ],
									"rnbo_classname" : "out~",
									"rnbo_extra_attributes" : 									{
										"comment" : "",
										"meta" : ""
									}
,
									"rnbo_serial" : 3,
									"rnbo_uniqueid" : "out~_obj-78",
									"rnboinfo" : 									{
										"needsInstanceInfo" : 1,
										"argnames" : 										{
											"in1" : 											{
												"attrOrProp" : 1,
												"digest" : "signal sent to outlet with index 14",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 0,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"touched" : 0,
												"inlet" : 1,
												"type" : "signal"
											}
,
											"index" : 											{
												"attrOrProp" : 2,
												"digest" : "outlet number",
												"defaultarg" : 1,
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"touched" : 0,
												"type" : "number",
												"mandatory" : 1
											}
,
											"comment" : 											{
												"attrOrProp" : 2,
												"digest" : "mouse over comment",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"touched" : 0,
												"type" : "symbol"
											}
,
											"meta" : 											{
												"attrOrProp" : 2,
												"digest" : "A JSON formatted string containing metadata for use by the exported code",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"touched" : 0,
												"type" : "symbol",
												"defaultValue" : "",
												"label" : "Metadata",
												"displayorder" : 3
											}

										}
,
										"inputs" : [ 											{
												"name" : "in1",
												"type" : "signal",
												"digest" : "signal sent to outlet with index 14",
												"displayName" : "",
												"hot" : 1,
												"docked" : 0
											}
 ],
										"outputs" : [  ],
										"helpname" : "out~",
										"aliasOf" : "out~",
										"classname" : "out~",
										"operator" : 0,
										"versionId" : 1989326771,
										"changesPatcherIO" : 1
									}
,
									"text" : "out~ 14"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-80",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 456.796110242605209, 876.699017107486725, 50.0, 23.0 ],
									"rnbo_classname" : "out~",
									"rnbo_extra_attributes" : 									{
										"comment" : "",
										"meta" : ""
									}
,
									"rnbo_serial" : 4,
									"rnbo_uniqueid" : "out~_obj-80",
									"rnboinfo" : 									{
										"needsInstanceInfo" : 1,
										"argnames" : 										{
											"in1" : 											{
												"attrOrProp" : 1,
												"digest" : "signal sent to outlet with index 13",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 0,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"touched" : 0,
												"inlet" : 1,
												"type" : "signal"
											}
,
											"index" : 											{
												"attrOrProp" : 2,
												"digest" : "outlet number",
												"defaultarg" : 1,
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"touched" : 0,
												"type" : "number",
												"mandatory" : 1
											}
,
											"comment" : 											{
												"attrOrProp" : 2,
												"digest" : "mouse over comment",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"touched" : 0,
												"type" : "symbol"
											}
,
											"meta" : 											{
												"attrOrProp" : 2,
												"digest" : "A JSON formatted string containing metadata for use by the exported code",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"touched" : 0,
												"type" : "symbol",
												"defaultValue" : "",
												"label" : "Metadata",
												"displayorder" : 3
											}

										}
,
										"inputs" : [ 											{
												"name" : "in1",
												"type" : "signal",
												"digest" : "signal sent to outlet with index 13",
												"displayName" : "",
												"hot" : 1,
												"docked" : 0
											}
 ],
										"outputs" : [  ],
										"helpname" : "out~",
										"aliasOf" : "out~",
										"classname" : "out~",
										"operator" : 0,
										"versionId" : 1989326771,
										"changesPatcherIO" : 1
									}
,
									"text" : "out~ 13"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-69",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 434.466013461351395, 847.087367027997971, 50.0, 23.0 ],
									"rnbo_classname" : "out~",
									"rnbo_extra_attributes" : 									{
										"comment" : "",
										"meta" : ""
									}
,
									"rnbo_serial" : 5,
									"rnbo_uniqueid" : "out~_obj-69",
									"rnboinfo" : 									{
										"needsInstanceInfo" : 1,
										"argnames" : 										{
											"in1" : 											{
												"attrOrProp" : 1,
												"digest" : "signal sent to outlet with index 12",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 0,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"touched" : 0,
												"inlet" : 1,
												"type" : "signal"
											}
,
											"index" : 											{
												"attrOrProp" : 2,
												"digest" : "outlet number",
												"defaultarg" : 1,
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"touched" : 0,
												"type" : "number",
												"mandatory" : 1
											}
,
											"comment" : 											{
												"attrOrProp" : 2,
												"digest" : "mouse over comment",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"touched" : 0,
												"type" : "symbol"
											}
,
											"meta" : 											{
												"attrOrProp" : 2,
												"digest" : "A JSON formatted string containing metadata for use by the exported code",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"touched" : 0,
												"type" : "symbol",
												"defaultValue" : "",
												"label" : "Metadata",
												"displayorder" : 3
											}

										}
,
										"inputs" : [ 											{
												"name" : "in1",
												"type" : "signal",
												"digest" : "signal sent to outlet with index 12",
												"displayName" : "",
												"hot" : 1,
												"docked" : 0
											}
 ],
										"outputs" : [  ],
										"helpname" : "out~",
										"aliasOf" : "out~",
										"classname" : "out~",
										"operator" : 0,
										"versionId" : 1989326771,
										"changesPatcherIO" : 1
									}
,
									"text" : "out~ 12"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-71",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 414.077664226293564, 816.019406288862228, 50.0, 23.0 ],
									"rnbo_classname" : "out~",
									"rnbo_extra_attributes" : 									{
										"comment" : "",
										"meta" : ""
									}
,
									"rnbo_serial" : 6,
									"rnbo_uniqueid" : "out~_obj-71",
									"rnboinfo" : 									{
										"needsInstanceInfo" : 1,
										"argnames" : 										{
											"in1" : 											{
												"attrOrProp" : 1,
												"digest" : "signal sent to outlet with index 11",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 0,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"touched" : 0,
												"inlet" : 1,
												"type" : "signal"
											}
,
											"index" : 											{
												"attrOrProp" : 2,
												"digest" : "outlet number",
												"defaultarg" : 1,
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"touched" : 0,
												"type" : "number",
												"mandatory" : 1
											}
,
											"comment" : 											{
												"attrOrProp" : 2,
												"digest" : "mouse over comment",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"touched" : 0,
												"type" : "symbol"
											}
,
											"meta" : 											{
												"attrOrProp" : 2,
												"digest" : "A JSON formatted string containing metadata for use by the exported code",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"touched" : 0,
												"type" : "symbol",
												"defaultValue" : "",
												"label" : "Metadata",
												"displayorder" : 3
											}

										}
,
										"inputs" : [ 											{
												"name" : "in1",
												"type" : "signal",
												"digest" : "signal sent to outlet with index 11",
												"displayName" : "",
												"hot" : 1,
												"docked" : 0
											}
 ],
										"outputs" : [  ],
										"helpname" : "out~",
										"aliasOf" : "out~",
										"classname" : "out~",
										"operator" : 0,
										"versionId" : 1989326771,
										"changesPatcherIO" : 1
									}
,
									"text" : "out~ 11"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-72",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 391.747567445039749, 785.922319322824478, 50.0, 23.0 ],
									"rnbo_classname" : "out~",
									"rnbo_extra_attributes" : 									{
										"comment" : "",
										"meta" : ""
									}
,
									"rnbo_serial" : 7,
									"rnbo_uniqueid" : "out~_obj-72",
									"rnboinfo" : 									{
										"needsInstanceInfo" : 1,
										"argnames" : 										{
											"in1" : 											{
												"attrOrProp" : 1,
												"digest" : "signal sent to outlet with index 10",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 0,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"touched" : 0,
												"inlet" : 1,
												"type" : "signal"
											}
,
											"index" : 											{
												"attrOrProp" : 2,
												"digest" : "outlet number",
												"defaultarg" : 1,
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"touched" : 0,
												"type" : "number",
												"mandatory" : 1
											}
,
											"comment" : 											{
												"attrOrProp" : 2,
												"digest" : "mouse over comment",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"touched" : 0,
												"type" : "symbol"
											}
,
											"meta" : 											{
												"attrOrProp" : 2,
												"digest" : "A JSON formatted string containing metadata for use by the exported code",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"touched" : 0,
												"type" : "symbol",
												"defaultValue" : "",
												"label" : "Metadata",
												"displayorder" : 3
											}

										}
,
										"inputs" : [ 											{
												"name" : "in1",
												"type" : "signal",
												"digest" : "signal sent to outlet with index 10",
												"displayName" : "",
												"hot" : 1,
												"docked" : 0
											}
 ],
										"outputs" : [  ],
										"helpname" : "out~",
										"aliasOf" : "out~",
										"classname" : "out~",
										"operator" : 0,
										"versionId" : 1989326771,
										"changesPatcherIO" : 1
									}
,
									"text" : "out~ 10"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-74",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 370.873781323432922, 758.252416789531708, 43.0, 23.0 ],
									"rnbo_classname" : "out~",
									"rnbo_extra_attributes" : 									{
										"comment" : "",
										"meta" : ""
									}
,
									"rnbo_serial" : 8,
									"rnbo_uniqueid" : "out~_obj-74",
									"rnboinfo" : 									{
										"needsInstanceInfo" : 1,
										"argnames" : 										{
											"in1" : 											{
												"attrOrProp" : 1,
												"digest" : "signal sent to outlet with index 9",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 0,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"touched" : 0,
												"inlet" : 1,
												"type" : "signal"
											}
,
											"index" : 											{
												"attrOrProp" : 2,
												"digest" : "outlet number",
												"defaultarg" : 1,
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"touched" : 0,
												"type" : "number",
												"mandatory" : 1
											}
,
											"comment" : 											{
												"attrOrProp" : 2,
												"digest" : "mouse over comment",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"touched" : 0,
												"type" : "symbol"
											}
,
											"meta" : 											{
												"attrOrProp" : 2,
												"digest" : "A JSON formatted string containing metadata for use by the exported code",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"touched" : 0,
												"type" : "symbol",
												"defaultValue" : "",
												"label" : "Metadata",
												"displayorder" : 3
											}

										}
,
										"inputs" : [ 											{
												"name" : "in1",
												"type" : "signal",
												"digest" : "signal sent to outlet with index 9",
												"displayName" : "",
												"hot" : 1,
												"docked" : 0
											}
 ],
										"outputs" : [  ],
										"helpname" : "out~",
										"aliasOf" : "out~",
										"classname" : "out~",
										"operator" : 0,
										"versionId" : 1989326771,
										"changesPatcherIO" : 1
									}
,
									"text" : "out~ 9"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-63",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 350.485432088375092, 728.155329823493958, 43.0, 23.0 ],
									"rnbo_classname" : "out~",
									"rnbo_extra_attributes" : 									{
										"comment" : "",
										"meta" : ""
									}
,
									"rnbo_serial" : 9,
									"rnbo_uniqueid" : "out~_obj-63",
									"rnboinfo" : 									{
										"needsInstanceInfo" : 1,
										"argnames" : 										{
											"in1" : 											{
												"attrOrProp" : 1,
												"digest" : "signal sent to outlet with index 8",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 0,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"touched" : 0,
												"inlet" : 1,
												"type" : "signal"
											}
,
											"index" : 											{
												"attrOrProp" : 2,
												"digest" : "outlet number",
												"defaultarg" : 1,
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"touched" : 0,
												"type" : "number",
												"mandatory" : 1
											}
,
											"comment" : 											{
												"attrOrProp" : 2,
												"digest" : "mouse over comment",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"touched" : 0,
												"type" : "symbol"
											}
,
											"meta" : 											{
												"attrOrProp" : 2,
												"digest" : "A JSON formatted string containing metadata for use by the exported code",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"touched" : 0,
												"type" : "symbol",
												"defaultValue" : "",
												"label" : "Metadata",
												"displayorder" : 3
											}

										}
,
										"inputs" : [ 											{
												"name" : "in1",
												"type" : "signal",
												"digest" : "signal sent to outlet with index 8",
												"displayName" : "",
												"hot" : 1,
												"docked" : 0
											}
 ],
										"outputs" : [  ],
										"helpname" : "out~",
										"aliasOf" : "out~",
										"classname" : "out~",
										"operator" : 0,
										"versionId" : 1989326771,
										"changesPatcherIO" : 1
									}
,
									"text" : "out~ 8"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-65",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 329.611645966768265, 696.116495311260223, 43.0, 23.0 ],
									"rnbo_classname" : "out~",
									"rnbo_extra_attributes" : 									{
										"comment" : "",
										"meta" : ""
									}
,
									"rnbo_serial" : 10,
									"rnbo_uniqueid" : "out~_obj-65",
									"rnboinfo" : 									{
										"needsInstanceInfo" : 1,
										"argnames" : 										{
											"in1" : 											{
												"attrOrProp" : 1,
												"digest" : "signal sent to outlet with index 7",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 0,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"touched" : 0,
												"inlet" : 1,
												"type" : "signal"
											}
,
											"index" : 											{
												"attrOrProp" : 2,
												"digest" : "outlet number",
												"defaultarg" : 1,
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"touched" : 0,
												"type" : "number",
												"mandatory" : 1
											}
,
											"comment" : 											{
												"attrOrProp" : 2,
												"digest" : "mouse over comment",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"touched" : 0,
												"type" : "symbol"
											}
,
											"meta" : 											{
												"attrOrProp" : 2,
												"digest" : "A JSON formatted string containing metadata for use by the exported code",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"touched" : 0,
												"type" : "symbol",
												"defaultValue" : "",
												"label" : "Metadata",
												"displayorder" : 3
											}

										}
,
										"inputs" : [ 											{
												"name" : "in1",
												"type" : "signal",
												"digest" : "signal sent to outlet with index 7",
												"displayName" : "",
												"hot" : 1,
												"docked" : 0
											}
 ],
										"outputs" : [  ],
										"helpname" : "out~",
										"aliasOf" : "out~",
										"classname" : "out~",
										"operator" : 0,
										"versionId" : 1989326771,
										"changesPatcherIO" : 1
									}
,
									"text" : "out~ 7"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-66",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 307.28154918551445, 664.563097685575485, 43.0, 23.0 ],
									"rnbo_classname" : "out~",
									"rnbo_extra_attributes" : 									{
										"comment" : "",
										"meta" : ""
									}
,
									"rnbo_serial" : 11,
									"rnbo_uniqueid" : "out~_obj-66",
									"rnboinfo" : 									{
										"needsInstanceInfo" : 1,
										"argnames" : 										{
											"in1" : 											{
												"attrOrProp" : 1,
												"digest" : "signal sent to outlet with index 6",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 0,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"touched" : 0,
												"inlet" : 1,
												"type" : "signal"
											}
,
											"index" : 											{
												"attrOrProp" : 2,
												"digest" : "outlet number",
												"defaultarg" : 1,
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"touched" : 0,
												"type" : "number",
												"mandatory" : 1
											}
,
											"comment" : 											{
												"attrOrProp" : 2,
												"digest" : "mouse over comment",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"touched" : 0,
												"type" : "symbol"
											}
,
											"meta" : 											{
												"attrOrProp" : 2,
												"digest" : "A JSON formatted string containing metadata for use by the exported code",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"touched" : 0,
												"type" : "symbol",
												"defaultValue" : "",
												"label" : "Metadata",
												"displayorder" : 3
											}

										}
,
										"inputs" : [ 											{
												"name" : "in1",
												"type" : "signal",
												"digest" : "signal sent to outlet with index 6",
												"displayName" : "",
												"hot" : 1,
												"docked" : 0
											}
 ],
										"outputs" : [  ],
										"helpname" : "out~",
										"aliasOf" : "out~",
										"classname" : "out~",
										"operator" : 0,
										"versionId" : 1989326771,
										"changesPatcherIO" : 1
									}
,
									"text" : "out~ 6"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-68",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 286.407763063907623, 632.524263173341751, 43.0, 23.0 ],
									"rnbo_classname" : "out~",
									"rnbo_extra_attributes" : 									{
										"comment" : "",
										"meta" : ""
									}
,
									"rnbo_serial" : 12,
									"rnbo_uniqueid" : "out~_obj-68",
									"rnboinfo" : 									{
										"needsInstanceInfo" : 1,
										"argnames" : 										{
											"in1" : 											{
												"attrOrProp" : 1,
												"digest" : "signal sent to outlet with index 5",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 0,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"touched" : 0,
												"inlet" : 1,
												"type" : "signal"
											}
,
											"index" : 											{
												"attrOrProp" : 2,
												"digest" : "outlet number",
												"defaultarg" : 1,
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"touched" : 0,
												"type" : "number",
												"mandatory" : 1
											}
,
											"comment" : 											{
												"attrOrProp" : 2,
												"digest" : "mouse over comment",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"touched" : 0,
												"type" : "symbol"
											}
,
											"meta" : 											{
												"attrOrProp" : 2,
												"digest" : "A JSON formatted string containing metadata for use by the exported code",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"touched" : 0,
												"type" : "symbol",
												"defaultValue" : "",
												"label" : "Metadata",
												"displayorder" : 3
											}

										}
,
										"inputs" : [ 											{
												"name" : "in1",
												"type" : "signal",
												"digest" : "signal sent to outlet with index 5",
												"displayName" : "",
												"hot" : 1,
												"docked" : 0
											}
 ],
										"outputs" : [  ],
										"helpname" : "out~",
										"aliasOf" : "out~",
										"classname" : "out~",
										"operator" : 0,
										"versionId" : 1989326771,
										"changesPatcherIO" : 1
									}
,
									"text" : "out~ 5"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-52",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 263.592229396104813, 601.941739320755005, 43.0, 23.0 ],
									"rnbo_classname" : "out~",
									"rnbo_extra_attributes" : 									{
										"comment" : "",
										"meta" : ""
									}
,
									"rnbo_serial" : 13,
									"rnbo_uniqueid" : "out~_obj-52",
									"rnboinfo" : 									{
										"needsInstanceInfo" : 1,
										"argnames" : 										{
											"in1" : 											{
												"attrOrProp" : 1,
												"digest" : "signal sent to outlet with index 4",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 0,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"touched" : 0,
												"inlet" : 1,
												"type" : "signal"
											}
,
											"index" : 											{
												"attrOrProp" : 2,
												"digest" : "outlet number",
												"defaultarg" : 1,
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"touched" : 0,
												"type" : "number",
												"mandatory" : 1
											}
,
											"comment" : 											{
												"attrOrProp" : 2,
												"digest" : "mouse over comment",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"touched" : 0,
												"type" : "symbol"
											}
,
											"meta" : 											{
												"attrOrProp" : 2,
												"digest" : "A JSON formatted string containing metadata for use by the exported code",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"touched" : 0,
												"type" : "symbol",
												"defaultValue" : "",
												"label" : "Metadata",
												"displayorder" : 3
											}

										}
,
										"inputs" : [ 											{
												"name" : "in1",
												"type" : "signal",
												"digest" : "signal sent to outlet with index 4",
												"displayName" : "",
												"hot" : 1,
												"docked" : 0
											}
 ],
										"outputs" : [  ],
										"helpname" : "out~",
										"aliasOf" : "out~",
										"classname" : "out~",
										"operator" : 0,
										"versionId" : 1989326771,
										"changesPatcherIO" : 1
									}
,
									"text" : "out~ 4"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-54",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 243.203880161046982, 571.359215468168259, 43.0, 23.0 ],
									"rnbo_classname" : "out~",
									"rnbo_extra_attributes" : 									{
										"comment" : "",
										"meta" : ""
									}
,
									"rnbo_serial" : 14,
									"rnbo_uniqueid" : "out~_obj-54",
									"rnboinfo" : 									{
										"needsInstanceInfo" : 1,
										"argnames" : 										{
											"in1" : 											{
												"attrOrProp" : 1,
												"digest" : "signal sent to outlet with index 3",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 0,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"touched" : 0,
												"inlet" : 1,
												"type" : "signal"
											}
,
											"index" : 											{
												"attrOrProp" : 2,
												"digest" : "outlet number",
												"defaultarg" : 1,
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"touched" : 0,
												"type" : "number",
												"mandatory" : 1
											}
,
											"comment" : 											{
												"attrOrProp" : 2,
												"digest" : "mouse over comment",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"touched" : 0,
												"type" : "symbol"
											}
,
											"meta" : 											{
												"attrOrProp" : 2,
												"digest" : "A JSON formatted string containing metadata for use by the exported code",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"touched" : 0,
												"type" : "symbol",
												"defaultValue" : "",
												"label" : "Metadata",
												"displayorder" : 3
											}

										}
,
										"inputs" : [ 											{
												"name" : "in1",
												"type" : "signal",
												"digest" : "signal sent to outlet with index 3",
												"displayName" : "",
												"hot" : 1,
												"docked" : 0
											}
 ],
										"outputs" : [  ],
										"helpname" : "out~",
										"aliasOf" : "out~",
										"classname" : "out~",
										"operator" : 0,
										"versionId" : 1989326771,
										"changesPatcherIO" : 1
									}
,
									"text" : "out~ 3"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-43",
									"inc" : 1.072,
									"interp" : 0,
									"maxclass" : "gain~",
									"multichannelvariant" : 0,
									"numinlets" : 1,
									"numoutlets" : 2,
									"outlettype" : [ "signal", "" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 523.300963699817657, 349.5145583152771, 18.900342583656311, 140.206177711486816 ],
									"rnbo_classname" : "gain~",
									"rnbo_extra_attributes" : 									{
										"inc" : 1.072,
										"size" : 158.0,
										"scale" : 7.943,
										"order" : "",
										"preset" : 0
									}
,
									"rnbo_serial" : 1,
									"rnbo_uniqueid" : "gain~_obj-43",
									"scale" : 7.943,
									"size" : 158.0
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-44",
									"inc" : 1.072,
									"interp" : 0,
									"maxclass" : "gain~",
									"multichannelvariant" : 0,
									"numinlets" : 1,
									"numoutlets" : 2,
									"outlettype" : [ "signal", "" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 502.427177578210831, 349.5145583152771, 18.900342583656311, 140.206177711486816 ],
									"rnbo_classname" : "gain~",
									"rnbo_extra_attributes" : 									{
										"inc" : 1.072,
										"size" : 158.0,
										"scale" : 7.943,
										"order" : "",
										"preset" : 0
									}
,
									"rnbo_serial" : 2,
									"rnbo_uniqueid" : "gain~_obj-44",
									"scale" : 7.943,
									"size" : 158.0
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-45",
									"inc" : 1.072,
									"interp" : 0,
									"maxclass" : "gain~",
									"multichannelvariant" : 0,
									"numinlets" : 1,
									"numoutlets" : 2,
									"outlettype" : [ "signal", "" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 480.097080796957016, 349.5145583152771, 18.900342583656311, 140.206177711486816 ],
									"rnbo_classname" : "gain~",
									"rnbo_extra_attributes" : 									{
										"inc" : 1.072,
										"size" : 158.0,
										"scale" : 7.943,
										"order" : "",
										"preset" : 0
									}
,
									"rnbo_serial" : 3,
									"rnbo_uniqueid" : "gain~_obj-45",
									"scale" : 7.943,
									"size" : 158.0
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-46",
									"inc" : 1.072,
									"interp" : 0,
									"maxclass" : "gain~",
									"multichannelvariant" : 0,
									"numinlets" : 1,
									"numoutlets" : 2,
									"outlettype" : [ "signal", "" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 458.737857788801193, 349.5145583152771, 18.900342583656311, 140.206177711486816 ],
									"rnbo_classname" : "gain~",
									"rnbo_extra_attributes" : 									{
										"inc" : 1.072,
										"size" : 158.0,
										"scale" : 7.943,
										"order" : "",
										"preset" : 0
									}
,
									"rnbo_serial" : 4,
									"rnbo_uniqueid" : "gain~_obj-46",
									"scale" : 7.943,
									"size" : 158.0
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-47",
									"inc" : 1.072,
									"interp" : 0,
									"maxclass" : "gain~",
									"multichannelvariant" : 0,
									"numinlets" : 1,
									"numoutlets" : 2,
									"outlettype" : [ "signal", "" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 436.407761007547379, 349.5145583152771, 18.900342583656311, 140.206177711486816 ],
									"rnbo_classname" : "gain~",
									"rnbo_extra_attributes" : 									{
										"inc" : 1.072,
										"size" : 158.0,
										"scale" : 7.943,
										"order" : "",
										"preset" : 0
									}
,
									"rnbo_serial" : 5,
									"rnbo_uniqueid" : "gain~_obj-47",
									"scale" : 7.943,
									"size" : 158.0
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-49",
									"inc" : 1.072,
									"interp" : 0,
									"maxclass" : "gain~",
									"multichannelvariant" : 0,
									"numinlets" : 1,
									"numoutlets" : 2,
									"outlettype" : [ "signal", "" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 416.504848659038544, 349.5145583152771, 18.900342583656311, 140.206177711486816 ],
									"rnbo_classname" : "gain~",
									"rnbo_extra_attributes" : 									{
										"inc" : 1.072,
										"size" : 158.0,
										"scale" : 7.943,
										"order" : "",
										"preset" : 0
									}
,
									"rnbo_serial" : 6,
									"rnbo_uniqueid" : "gain~_obj-49",
									"scale" : 7.943,
									"size" : 158.0
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-50",
									"inc" : 1.072,
									"interp" : 0,
									"maxclass" : "gain~",
									"multichannelvariant" : 0,
									"numinlets" : 1,
									"numoutlets" : 2,
									"outlettype" : [ "signal", "" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 393.689314991235733, 349.5145583152771, 18.900342583656311, 140.206177711486816 ],
									"rnbo_classname" : "gain~",
									"rnbo_extra_attributes" : 									{
										"inc" : 1.072,
										"size" : 158.0,
										"scale" : 7.943,
										"order" : "",
										"preset" : 0
									}
,
									"rnbo_serial" : 7,
									"rnbo_uniqueid" : "gain~_obj-50",
									"scale" : 7.943,
									"size" : 158.0
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-51",
									"inc" : 1.072,
									"interp" : 0,
									"maxclass" : "gain~",
									"multichannelvariant" : 0,
									"numinlets" : 1,
									"numoutlets" : 2,
									"outlettype" : [ "signal", "" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 372.815528869628906, 349.5145583152771, 18.900342583656311, 140.206177711486816 ],
									"rnbo_classname" : "gain~",
									"rnbo_extra_attributes" : 									{
										"inc" : 1.072,
										"size" : 158.0,
										"scale" : 7.943,
										"order" : "",
										"preset" : 0
									}
,
									"rnbo_serial" : 8,
									"rnbo_uniqueid" : "gain~_obj-51",
									"scale" : 7.943,
									"size" : 158.0
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-39",
									"inc" : 1.072,
									"interp" : 0,
									"maxclass" : "gain~",
									"multichannelvariant" : 0,
									"numinlets" : 1,
									"numoutlets" : 2,
									"outlettype" : [ "signal", "" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 352.427179634571075, 349.5145583152771, 18.900342583656311, 140.206177711486816 ],
									"rnbo_classname" : "gain~",
									"rnbo_extra_attributes" : 									{
										"inc" : 1.072,
										"size" : 158.0,
										"scale" : 7.943,
										"order" : "",
										"preset" : 0
									}
,
									"rnbo_serial" : 9,
									"rnbo_uniqueid" : "gain~_obj-39",
									"scale" : 7.943,
									"size" : 158.0
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-40",
									"inc" : 1.072,
									"interp" : 0,
									"maxclass" : "gain~",
									"multichannelvariant" : 0,
									"numinlets" : 1,
									"numoutlets" : 2,
									"outlettype" : [ "signal", "" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 331.553393512964249, 349.5145583152771, 18.900342583656311, 140.206177711486816 ],
									"rnbo_classname" : "gain~",
									"rnbo_extra_attributes" : 									{
										"inc" : 1.072,
										"size" : 158.0,
										"scale" : 7.943,
										"order" : "",
										"preset" : 0
									}
,
									"rnbo_serial" : 10,
									"rnbo_uniqueid" : "gain~_obj-40",
									"scale" : 7.943,
									"size" : 158.0
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-41",
									"inc" : 1.072,
									"interp" : 0,
									"maxclass" : "gain~",
									"multichannelvariant" : 0,
									"numinlets" : 1,
									"numoutlets" : 2,
									"outlettype" : [ "signal", "" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 309.223296731710434, 349.5145583152771, 18.900342583656311, 140.206177711486816 ],
									"rnbo_classname" : "gain~",
									"rnbo_extra_attributes" : 									{
										"inc" : 1.072,
										"size" : 158.0,
										"scale" : 7.943,
										"order" : "",
										"preset" : 0
									}
,
									"rnbo_serial" : 11,
									"rnbo_uniqueid" : "gain~_obj-41",
									"scale" : 7.943,
									"size" : 158.0
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-42",
									"inc" : 1.072,
									"interp" : 0,
									"maxclass" : "gain~",
									"multichannelvariant" : 0,
									"numinlets" : 1,
									"numoutlets" : 2,
									"outlettype" : [ "signal", "" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 288.349510610103607, 349.5145583152771, 18.900342583656311, 140.206177711486816 ],
									"rnbo_classname" : "gain~",
									"rnbo_extra_attributes" : 									{
										"inc" : 1.072,
										"size" : 158.0,
										"scale" : 7.943,
										"order" : "",
										"preset" : 0
									}
,
									"rnbo_serial" : 12,
									"rnbo_uniqueid" : "gain~_obj-42",
									"scale" : 7.943,
									"size" : 158.0
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-37",
									"inc" : 1.072,
									"interp" : 0,
									"maxclass" : "gain~",
									"multichannelvariant" : 0,
									"numinlets" : 1,
									"numoutlets" : 2,
									"outlettype" : [ "signal", "" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 266.019413828849792, 349.5145583152771, 18.900342583656311, 140.206177711486816 ],
									"rnbo_classname" : "gain~",
									"rnbo_extra_attributes" : 									{
										"inc" : 1.072,
										"size" : 158.0,
										"scale" : 7.943,
										"order" : "",
										"preset" : 0
									}
,
									"rnbo_serial" : 13,
									"rnbo_uniqueid" : "gain~_obj-37",
									"scale" : 7.943,
									"size" : 158.0
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-38",
									"inc" : 1.072,
									"interp" : 0,
									"maxclass" : "gain~",
									"multichannelvariant" : 0,
									"numinlets" : 1,
									"numoutlets" : 2,
									"outlettype" : [ "signal", "" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 245.145627707242966, 349.5145583152771, 18.900342583656311, 140.206177711486816 ],
									"rnbo_classname" : "gain~",
									"rnbo_extra_attributes" : 									{
										"inc" : 1.072,
										"size" : 158.0,
										"scale" : 7.943,
										"order" : "",
										"preset" : 0
									}
,
									"rnbo_serial" : 14,
									"rnbo_uniqueid" : "gain~_obj-38",
									"scale" : 7.943,
									"size" : 158.0
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-36",
									"inc" : 1.072,
									"interp" : 0,
									"maxclass" : "gain~",
									"multichannelvariant" : 0,
									"numinlets" : 1,
									"numoutlets" : 2,
									"outlettype" : [ "signal", "" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 222.815530925989151, 349.5145583152771, 18.900342583656311, 140.206177711486816 ],
									"rnbo_classname" : "gain~",
									"rnbo_extra_attributes" : 									{
										"inc" : 1.072,
										"size" : 158.0,
										"scale" : 7.943,
										"order" : "",
										"preset" : 0
									}
,
									"rnbo_serial" : 15,
									"rnbo_uniqueid" : "gain~_obj-36",
									"scale" : 7.943,
									"size" : 158.0
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-20",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 220.873783379793167, 538.349507182836533, 43.0, 23.0 ],
									"rnbo_classname" : "out~",
									"rnbo_extra_attributes" : 									{
										"comment" : "",
										"meta" : ""
									}
,
									"rnbo_serial" : 15,
									"rnbo_uniqueid" : "out~_obj-20",
									"rnboinfo" : 									{
										"needsInstanceInfo" : 1,
										"argnames" : 										{
											"in1" : 											{
												"attrOrProp" : 1,
												"digest" : "signal sent to outlet with index 2",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 0,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"touched" : 0,
												"inlet" : 1,
												"type" : "signal"
											}
,
											"index" : 											{
												"attrOrProp" : 2,
												"digest" : "outlet number",
												"defaultarg" : 1,
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"touched" : 0,
												"type" : "number",
												"mandatory" : 1
											}
,
											"comment" : 											{
												"attrOrProp" : 2,
												"digest" : "mouse over comment",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"touched" : 0,
												"type" : "symbol"
											}
,
											"meta" : 											{
												"attrOrProp" : 2,
												"digest" : "A JSON formatted string containing metadata for use by the exported code",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"touched" : 0,
												"type" : "symbol",
												"defaultValue" : "",
												"label" : "Metadata",
												"displayorder" : 3
											}

										}
,
										"inputs" : [ 											{
												"name" : "in1",
												"type" : "signal",
												"digest" : "signal sent to outlet with index 2",
												"displayName" : "",
												"hot" : 1,
												"docked" : 0
											}
 ],
										"outputs" : [  ],
										"helpname" : "out~",
										"aliasOf" : "out~",
										"classname" : "out~",
										"operator" : 0,
										"versionId" : 1989326771,
										"changesPatcherIO" : 1
									}
,
									"text" : "out~ 2"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-56",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 199.99999725818634, 505.825235784053802, 43.0, 23.0 ],
									"rnbo_classname" : "out~",
									"rnbo_extra_attributes" : 									{
										"comment" : "",
										"meta" : ""
									}
,
									"rnbo_serial" : 16,
									"rnbo_uniqueid" : "out~_obj-56",
									"rnboinfo" : 									{
										"needsInstanceInfo" : 1,
										"argnames" : 										{
											"in1" : 											{
												"attrOrProp" : 1,
												"digest" : "signal sent to outlet with index 1",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 0,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"touched" : 0,
												"inlet" : 1,
												"type" : "signal"
											}
,
											"index" : 											{
												"attrOrProp" : 2,
												"digest" : "outlet number",
												"defaultarg" : 1,
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"touched" : 0,
												"type" : "number",
												"mandatory" : 1
											}
,
											"comment" : 											{
												"attrOrProp" : 2,
												"digest" : "mouse over comment",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"touched" : 0,
												"type" : "symbol"
											}
,
											"meta" : 											{
												"attrOrProp" : 2,
												"digest" : "A JSON formatted string containing metadata for use by the exported code",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"touched" : 0,
												"type" : "symbol",
												"defaultValue" : "",
												"label" : "Metadata",
												"displayorder" : 3
											}

										}
,
										"inputs" : [ 											{
												"name" : "in1",
												"type" : "signal",
												"digest" : "signal sent to outlet with index 1",
												"displayName" : "",
												"hot" : 1,
												"docked" : 0
											}
 ],
										"outputs" : [  ],
										"helpname" : "out~",
										"aliasOf" : "out~",
										"classname" : "out~",
										"operator" : 0,
										"versionId" : 1989326771,
										"changesPatcherIO" : 1
									}
,
									"text" : "out~ 1"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-48",
									"inc" : 1.072,
									"interp" : 0,
									"maxclass" : "gain~",
									"multichannelvariant" : 0,
									"numinlets" : 1,
									"numoutlets" : 2,
									"outlettype" : [ "signal", "" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 201.941744804382324, 349.5145583152771, 18.900342583656311, 140.206177711486816 ],
									"rnbo_classname" : "gain~",
									"rnbo_extra_attributes" : 									{
										"inc" : 1.072,
										"size" : 158.0,
										"scale" : 7.943,
										"order" : "",
										"preset" : 0
									}
,
									"rnbo_serial" : 16,
									"rnbo_uniqueid" : "gain~_obj-48",
									"scale" : 7.943,
									"size" : 158.0
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-18",
									"maxclass" : "newobj",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 202.42718169093132, 136.407765120267868, 67.0, 23.0 ],
									"rnbo_classname" : "delay",
									"rnbo_serial" : 6,
									"rnbo_uniqueid" : "delay_obj-18",
									"text" : "delay 4000"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-17",
									"maxclass" : "button",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "bang" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 202.42718169093132, 214.077666968107224, 24.0, 24.0 ],
									"rnbo_classname" : "button",
									"rnbo_serial" : 3,
									"rnbo_uniqueid" : "button_obj-17"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-14",
									"maxclass" : "toggle",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "int" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 370.388344436883926, 214.563103854656219, 24.0, 24.0 ],
									"rnbo_classname" : "toggle",
									"rnbo_extra_attributes" : 									{
										"order" : "",
										"preset" : 0
									}
,
									"rnbo_serial" : 1,
									"rnbo_uniqueid" : "toggle_obj-14"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-9",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 202.42718169093132, 38.961038589477539, 56.0, 23.0 ],
									"rnbo_classname" : "loadbang",
									"rnbo_serial" : 2,
									"rnbo_uniqueid" : "loadbang_obj-9",
									"text" : "loadbang"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-5",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 370.388344436883926, 262.621355623006821, 51.0, 23.0 ],
									"rnbo_classname" : "set",
									"rnbo_serial" : 1,
									"rnbo_uniqueid" : "set_obj-5",
									"rnboinfo" : 									{
										"needsInstanceInfo" : 1,
										"argnames" : 										{
											"name" : 											{
												"attrOrProp" : 2,
												"digest" : "attribute/param to control",
												"defaultarg" : 1,
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"touched" : 0,
												"type" : "symbol",
												"mandatory" : 1
											}

										}
,
										"inputs" : [ 											{
												"name" : "input",
												"type" : [ "bang", "number", "list", "signal" ],
												"digest" : "attribute or parameter value (bang, number, list)",
												"hot" : 1,
												"docked" : 0
											}
 ],
										"outputs" : [ 											{
												"name" : "output",
												"type" : [ "bang", "number", "list", "signal" ],
												"digest" : "connect to first inlet of gen or subpatcher",
												"docked" : 0
											}
 ],
										"helpname" : "set",
										"aliasOf" : "set",
										"classname" : "set",
										"operator" : 0,
										"versionId" : 1197449671,
										"changesPatcherIO" : 0
									}
,
									"text" : "set loop"
								}

							}
, 							{
								"box" : 								{
									"format" : 0,
									"id" : "obj-3",
									"maxclass" : "number",
									"numinlets" : 1,
									"numoutlets" : 2,
									"outlettype" : [ "", "bang" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 277.1844622194767, 214.563103854656219, 50.0, 23.0 ],
									"rnbo_classname" : "number",
									"rnbo_extra_attributes" : 									{
										"maximum" : "<none>",
										"minimum" : "<none>",
										"initialFormat" : "integer",
										"order" : "",
										"preset" : 0
									}
,
									"rnbo_serial" : 21,
									"rnbo_uniqueid" : "number_obj-3"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-15",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 277.1844622194767, 164.563104540109634, 50.0, 23.0 ],
									"rnbo_classname" : "message",
									"rnbo_extra_attributes" : 									{
										"text" : "",
										"storeempty" : 0
									}
,
									"rnbo_serial" : 2,
									"rnbo_uniqueid" : "message_obj-15",
									"text" : "8"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-29",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 277.1844622194767, 262.621355623006821, 73.0, 23.0 ],
									"rnbo_classname" : "set",
									"rnbo_serial" : 2,
									"rnbo_uniqueid" : "set_obj-29",
									"rnboinfo" : 									{
										"needsInstanceInfo" : 1,
										"argnames" : 										{
											"name" : 											{
												"attrOrProp" : 2,
												"digest" : "attribute/param to control",
												"defaultarg" : 1,
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"touched" : 0,
												"type" : "symbol",
												"mandatory" : 1
											}

										}
,
										"inputs" : [ 											{
												"name" : "input",
												"type" : [ "bang", "number", "list", "signal" ],
												"digest" : "attribute or parameter value (bang, number, list)",
												"hot" : 1,
												"docked" : 0
											}
 ],
										"outputs" : [ 											{
												"name" : "output",
												"type" : [ "bang", "number", "list", "signal" ],
												"digest" : "connect to first inlet of gen or subpatcher",
												"docked" : 0
											}
 ],
										"helpname" : "set",
										"aliasOf" : "set",
										"classname" : "set",
										"operator" : 0,
										"versionId" : 1197449671,
										"changesPatcherIO" : 0
									}
,
									"text" : "set channels"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Lato",
									"fontsize" : 12.0,
									"id" : "obj-11",
									"maxclass" : "newobj",
									"numinlets" : 3,
									"numoutlets" : 17,
									"outlettype" : [ "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal" ],
									"patching_rect" : [ 201.941744804382324, 317.475723803043365, 434.0, 23.0 ],
									"rnbo_classname" : "groove~",
									"rnbo_serial" : 1,
									"rnbo_uniqueid" : "groove~_obj-11",
									"rnboinfo" : 									{
										"needsInstanceInfo" : 1,
										"argnames" : 										{
											"rate" : 											{
												"attrOrProp" : 1,
												"digest" : "Playback rate.",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"touched" : 0,
												"inlet" : 1,
												"type" : "number",
												"defaultValue" : "1"
											}
,
											"jumpto" : 											{
												"attrOrProp" : 1,
												"digest" : "Jump to position (ms) and start playback.",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 0,
												"attachable" : 1,
												"isparam" : 0,
												"deprecated" : 0,
												"touched" : 0,
												"type" : "number",
												"defaultValue" : "-1"
											}
,
											"begin" : 											{
												"attrOrProp" : 1,
												"digest" : "Loop min (ms).",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"touched" : 0,
												"inlet" : 1,
												"type" : "number",
												"defaultValue" : "0"
											}
,
											"end" : 											{
												"attrOrProp" : 1,
												"digest" : "Loop max (ms).",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"touched" : 0,
												"inlet" : 1,
												"type" : "number",
												"defaultValue" : "-1"
											}
,
											"out1" : 											{
												"attrOrProp" : 1,
												"digest" : "The sample output.",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 0,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"touched" : 0,
												"outlet" : 1,
												"type" : "signal"
											}
,
											"out2" : 											{
												"attrOrProp" : 1,
												"digest" : "The sample output.",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 0,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"touched" : 0,
												"outlet" : 1,
												"type" : "signal"
											}
,
											"out3" : 											{
												"attrOrProp" : 1,
												"digest" : "The sample output.",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 0,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"touched" : 0,
												"outlet" : 1,
												"type" : "signal"
											}
,
											"out4" : 											{
												"attrOrProp" : 1,
												"digest" : "The sample output.",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 0,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"touched" : 0,
												"outlet" : 1,
												"type" : "signal"
											}
,
											"out5" : 											{
												"attrOrProp" : 1,
												"digest" : "The sample output.",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 0,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"touched" : 0,
												"outlet" : 1,
												"type" : "signal"
											}
,
											"out6" : 											{
												"attrOrProp" : 1,
												"digest" : "The sample output.",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 0,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"touched" : 0,
												"outlet" : 1,
												"type" : "signal"
											}
,
											"out7" : 											{
												"attrOrProp" : 1,
												"digest" : "The sample output.",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 0,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"touched" : 0,
												"outlet" : 1,
												"type" : "signal"
											}
,
											"out8" : 											{
												"attrOrProp" : 1,
												"digest" : "The sample output.",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 0,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"touched" : 0,
												"outlet" : 1,
												"type" : "signal"
											}
,
											"out9" : 											{
												"attrOrProp" : 1,
												"digest" : "The sample output.",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 0,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"touched" : 0,
												"outlet" : 1,
												"type" : "signal"
											}
,
											"out10" : 											{
												"attrOrProp" : 1,
												"digest" : "The sample output.",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 0,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"touched" : 0,
												"outlet" : 1,
												"type" : "signal"
											}
,
											"out11" : 											{
												"attrOrProp" : 1,
												"digest" : "The sample output.",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 0,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"touched" : 0,
												"outlet" : 1,
												"type" : "signal"
											}
,
											"out12" : 											{
												"attrOrProp" : 1,
												"digest" : "The sample output.",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 0,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"touched" : 0,
												"outlet" : 1,
												"type" : "signal"
											}
,
											"out13" : 											{
												"attrOrProp" : 1,
												"digest" : "The sample output.",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 0,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"touched" : 0,
												"outlet" : 1,
												"type" : "signal"
											}
,
											"out14" : 											{
												"attrOrProp" : 1,
												"digest" : "The sample output.",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 0,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"touched" : 0,
												"outlet" : 1,
												"type" : "signal"
											}
,
											"out15" : 											{
												"attrOrProp" : 1,
												"digest" : "The sample output.",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 0,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"touched" : 0,
												"outlet" : 1,
												"type" : "signal"
											}
,
											"out16" : 											{
												"attrOrProp" : 1,
												"digest" : "The sample output.",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 0,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"touched" : 0,
												"outlet" : 1,
												"type" : "signal"
											}
,
											"sync" : 											{
												"attrOrProp" : 1,
												"digest" : "Sync output (phase, samples, ms)",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 0,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"touched" : 0,
												"outlet" : 1,
												"type" : "signal"
											}
,
											"loop" : 											{
												"attrOrProp" : 1,
												"digest" : "The word loop, followed by a `0` or `1`, disables/enables looping.",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 1,
												"isparam" : 0,
												"deprecated" : 0,
												"touched" : 0,
												"type" : "number",
												"defaultValue" : "1"
											}
,
											"crossfade" : 											{
												"attrOrProp" : 1,
												"digest" : "Enable an attempted crossfade on loop jumpback. The fade depends on available sample material (ms).",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 1,
												"isparam" : 0,
												"deprecated" : 0,
												"touched" : 0,
												"type" : "number",
												"defaultValue" : "0"
											}
,
											"stop" : 											{
												"attrOrProp" : 1,
												"digest" : "Stops the playback of the buffer.",
												"isalias" : 0,
												"aliases" : [  ],
												"attachable" : 1,
												"isparam" : 0,
												"deprecated" : 0,
												"touched" : 0,
												"type" : "bang"
											}
,
											"buffer" : 											{
												"attrOrProp" : 1,
												"digest" : "If multiple buffer names are declared to be used, this sets the currently active buffer using an index [0 based].",
												"isalias" : 0,
												"aliases" : [  ],
												"attachable" : 1,
												"isparam" : 0,
												"deprecated" : 0,
												"touched" : 0,
												"type" : "number",
												"defaultValue" : "0"
											}
,
											"buffername" : 											{
												"attrOrProp" : 2,
												"digest" : "Buffer to use",
												"defaultarg" : 1,
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"touched" : 0,
												"type" : "symbol",
												"mandatory" : 1
											}
,
											"channels" : 											{
												"attrOrProp" : 2,
												"digest" : "Number of channels to read.",
												"defaultarg" : 2,
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"touched" : 0,
												"type" : "number",
												"defaultValue" : "1"
											}
,
											"syncmode" : 											{
												"attrOrProp" : 2,
												"digest" : "Determines if the sync outlet reports phase (0..1), samples or milliseconds.",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"touched" : 0,
												"enum" : [ "phase", "samples", "ms" ],
												"type" : "enum",
												"defaultValue" : "phase"
											}
,
											"synctype" : 											{
												"attrOrProp" : 2,
												"digest" : "Set the sync signal to be relative to the loop length or absolute to the clip length.",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"touched" : 0,
												"enum" : [ "relative", "absolute" ],
												"type" : "enum",
												"defaultValue" : "relative"
											}

										}
,
										"inputs" : [ 											{
												"name" : "rate",
												"type" : [ "bang", "auto" ],
												"digest" : "Playback rate.",
												"hot" : 1,
												"docked" : 0
											}
, 											{
												"name" : "begin",
												"type" : "auto",
												"digest" : "Loop min (ms).",
												"docked" : 0
											}
, 											{
												"name" : "end",
												"type" : "auto",
												"digest" : "Loop max (ms).",
												"docked" : 0
											}
 ],
										"outputs" : [ 											{
												"name" : "out1",
												"type" : "signal",
												"digest" : "The sample output.",
												"docked" : 0
											}
, 											{
												"name" : "out2",
												"type" : "signal",
												"digest" : "The sample output.",
												"docked" : 0
											}
, 											{
												"name" : "out3",
												"type" : "signal",
												"digest" : "The sample output.",
												"docked" : 0
											}
, 											{
												"name" : "out4",
												"type" : "signal",
												"digest" : "The sample output.",
												"docked" : 0
											}
, 											{
												"name" : "out5",
												"type" : "signal",
												"digest" : "The sample output.",
												"docked" : 0
											}
, 											{
												"name" : "out6",
												"type" : "signal",
												"digest" : "The sample output.",
												"docked" : 0
											}
, 											{
												"name" : "out7",
												"type" : "signal",
												"digest" : "The sample output.",
												"docked" : 0
											}
, 											{
												"name" : "out8",
												"type" : "signal",
												"digest" : "The sample output.",
												"docked" : 0
											}
, 											{
												"name" : "out9",
												"type" : "signal",
												"digest" : "The sample output.",
												"docked" : 0
											}
, 											{
												"name" : "out10",
												"type" : "signal",
												"digest" : "The sample output.",
												"docked" : 0
											}
, 											{
												"name" : "out11",
												"type" : "signal",
												"digest" : "The sample output.",
												"docked" : 0
											}
, 											{
												"name" : "out12",
												"type" : "signal",
												"digest" : "The sample output.",
												"docked" : 0
											}
, 											{
												"name" : "out13",
												"type" : "signal",
												"digest" : "The sample output.",
												"docked" : 0
											}
, 											{
												"name" : "out14",
												"type" : "signal",
												"digest" : "The sample output.",
												"docked" : 0
											}
, 											{
												"name" : "out15",
												"type" : "signal",
												"digest" : "The sample output.",
												"docked" : 0
											}
, 											{
												"name" : "out16",
												"type" : "signal",
												"digest" : "The sample output.",
												"docked" : 0
											}
, 											{
												"name" : "sync",
												"type" : "signal",
												"digest" : "Sync output (phase, samples, ms)",
												"docked" : 0
											}
 ],
										"helpname" : "groove~",
										"aliasOf" : "groove~",
										"classname" : "groove~",
										"operator" : 0,
										"versionId" : -147380827,
										"changesPatcherIO" : 0
									}
,
									"text" : "groove~ playback 16 @buffername playback @syncmode ms @synctype absolute"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-8",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 431.067955255508423, 202.42718169093132, 98.0, 23.0 ],
									"rnbo_classname" : "outport",
									"rnbo_extra_attributes" : 									{
										"meta" : ""
									}
,
									"rnbo_serial" : 12,
									"rnbo_uniqueid" : "outport_obj-8",
									"text" : "outport channels"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-7",
									"linecount" : 3,
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 3,
									"outlettype" : [ "", "", "" ],
									"patching_rect" : [ 549.51455557346344, 169.417473405599594, 245.0, 52.0 ],
									"rnbo_classname" : "buffer~",
									"rnbo_extra_attributes" : 									{
										"fill" : "",
										"meta" : "",
										"samplerate" : 0.0,
										"type" : "",
										"preset" : 0
									}
,
									"rnbo_serial" : 1,
									"rnbo_uniqueid" : "buffer~_obj-7",
									"rnboinfo" : 									{
										"needsInstanceInfo" : 1,
										"argnames" : 										{
											"info" : 											{
												"attrOrProp" : 1,
												"digest" : "Bang to report buffer information.",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 0,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"touched" : 0,
												"inlet" : 1,
												"type" : "bang"
											}
,
											"sizeout" : 											{
												"attrOrProp" : 1,
												"digest" : "Size in Samples",
												"defaultarg" : 2,
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 0,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"touched" : 0,
												"outlet" : 1,
												"type" : "number",
												"defaultValue" : "0"
											}
,
											"chanout" : 											{
												"attrOrProp" : 1,
												"digest" : "Number of Channels",
												"isalias" : 0,
												"aliases" : [  ],
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"touched" : 0,
												"outlet" : 1,
												"type" : "number",
												"defaultValue" : "0"
											}
,
											"srout" : 											{
												"attrOrProp" : 1,
												"digest" : "Sample rate",
												"isalias" : 0,
												"aliases" : [  ],
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"touched" : 0,
												"outlet" : 1,
												"type" : "number",
												"defaultValue" : "0"
											}
,
											"size" : 											{
												"attrOrProp" : 1,
												"digest" : "Size in Samples. Take care when setting, allocation might block audio processing.",
												"defaultarg" : 2,
												"isalias" : 0,
												"aliases" : [ "samples" ],
												"settable" : 1,
												"attachable" : 1,
												"isparam" : 0,
												"deprecated" : 0,
												"touched" : 0,
												"type" : "number",
												"defaultValue" : "0"
											}
,
											"samples" : 											{
												"attrOrProp" : 1,
												"digest" : "Size in Samples. Take care when setting, allocation might block audio processing.",
												"defaultarg" : 2,
												"isalias" : 1,
												"aliasOf" : "size",
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 1,
												"isparam" : 0,
												"deprecated" : 0,
												"touched" : 0,
												"type" : "number",
												"defaultValue" : "0"
											}
,
											"sizems" : 											{
												"attrOrProp" : 1,
												"digest" : "Size in Milliseconds. Take care when setting, allocation might block audio processing.",
												"isalias" : 0,
												"aliases" : [ "ms" ],
												"settable" : 1,
												"attachable" : 1,
												"isparam" : 0,
												"deprecated" : 0,
												"touched" : 0,
												"type" : "number",
												"defaultValue" : "0"
											}
,
											"ms" : 											{
												"attrOrProp" : 1,
												"digest" : "Size in Milliseconds. Take care when setting, allocation might block audio processing.",
												"isalias" : 1,
												"aliasOf" : "sizems",
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 1,
												"isparam" : 0,
												"deprecated" : 0,
												"touched" : 0,
												"type" : "number",
												"defaultValue" : "0"
											}
,
											"clear" : 											{
												"attrOrProp" : 1,
												"digest" : "Clear the contents of the buffer",
												"isalias" : 0,
												"aliases" : [  ],
												"attachable" : 1,
												"isparam" : 0,
												"deprecated" : 0,
												"touched" : 0,
												"type" : "bang"
											}
,
											"normalize" : 											{
												"attrOrProp" : 1,
												"digest" : "Find Maximum and normalize to the value given.",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 1,
												"isparam" : 0,
												"deprecated" : 0,
												"touched" : 0,
												"type" : "number",
												"defaultValue" : "0.995"
											}
,
											"channels" : 											{
												"attrOrProp" : 1,
												"digest" : "Change channel count. Take care when setting, allocation might block audio processing.",
												"defaultarg" : 3,
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 1,
												"isparam" : 0,
												"deprecated" : 0,
												"touched" : 0,
												"type" : "number",
												"defaultValue" : "1"
											}
,
											"name" : 											{
												"attrOrProp" : 2,
												"digest" : "Name of the data buffer",
												"defaultarg" : 1,
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"touched" : 0,
												"type" : "symbol",
												"mandatory" : 1
											}
,
											"file" : 											{
												"attrOrProp" : 2,
												"digest" : "File name/path or URL to load into buffer.",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"touched" : 0,
												"type" : "symbol"
											}
,
											"type" : 											{
												"attrOrProp" : 2,
												"digest" : "Type of Data (float32, float64)",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"touched" : 0,
												"type" : "symbol"
											}
,
											"samplerate" : 											{
												"attrOrProp" : 2,
												"digest" : "Sample rate",
												"defaultarg" : 4,
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"touched" : 0,
												"type" : "number",
												"defaultValue" : "0"
											}
,
											"fill" : 											{
												"attrOrProp" : 2,
												"digest" : "Fill expression, this could be a value, or a simple function like sin(x), where x will run from 0 to 1 to fill the buffer.",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"touched" : 0,
												"type" : "symbol"
											}
,
											"external" : 											{
												"attrOrProp" : 2,
												"digest" : "Await data from the outside world.",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"touched" : 0,
												"type" : "bool",
												"doNotShowInMaxInspector" : 1
											}
,
											"preset" : 											{
												"attrOrProp" : 2,
												"digest" : "Add this value to the preset.",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"touched" : 0,
												"type" : "bool",
												"defaultValue" : "false",
												"label" : "Include In Preset",
												"category" : "Preset"
											}
,
											"meta" : 											{
												"attrOrProp" : 2,
												"digest" : "A JSON formatted string containing metadata for use by the exported code",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"touched" : 0,
												"type" : "symbol",
												"defaultValue" : "",
												"label" : "Metadata"
											}

										}
,
										"inputs" : [ 											{
												"name" : "info",
												"type" : "bang",
												"digest" : "Bang to report buffer information.",
												"hot" : 1,
												"docked" : 0
											}
 ],
										"outputs" : [ 											{
												"name" : "sizeout",
												"type" : "number",
												"digest" : "Size in Samples",
												"defaultarg" : 2,
												"docked" : 0
											}
, 											{
												"name" : "chanout",
												"type" : "number",
												"digest" : "Number of Channels",
												"docked" : 0
											}
, 											{
												"name" : "srout",
												"type" : "number",
												"digest" : "Sample rate",
												"docked" : 0
											}
 ],
										"helpname" : "buffer~",
										"aliasOf" : "data",
										"classname" : "buffer~",
										"operator" : 0,
										"versionId" : 405570163,
										"changesPatcherIO" : 0
									}
,
									"text" : "buffer~ playback @file /Users/josue/Music/UniversosParalelos.wav @channels 8"
								}

							}
, 							{
								"box" : 								{
									"format" : 0,
									"id" : "obj-6",
									"maxclass" : "number",
									"numinlets" : 1,
									"numoutlets" : 2,
									"outlettype" : [ "", "bang" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 392.718441218137741, 141.262133985757828, 85.333909690380096, 23.0 ],
									"rnbo_classname" : "number",
									"rnbo_extra_attributes" : 									{
										"maximum" : "<none>",
										"minimum" : "<none>",
										"initialFormat" : "integer",
										"order" : "",
										"preset" : 0
									}
,
									"rnbo_serial" : 22,
									"rnbo_uniqueid" : "number_obj-6"
								}

							}
, 							{
								"box" : 								{
									"format" : 0,
									"id" : "obj-4",
									"maxclass" : "number",
									"numinlets" : 1,
									"numoutlets" : 2,
									"outlettype" : [ "", "bang" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 431.067955255508423, 102.42718306183815, 50.0, 23.0 ],
									"rnbo_classname" : "number",
									"rnbo_extra_attributes" : 									{
										"maximum" : "<none>",
										"minimum" : "<none>",
										"initialFormat" : "integer",
										"order" : "",
										"preset" : 0
									}
,
									"rnbo_serial" : 23,
									"rnbo_uniqueid" : "number_obj-4"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-1",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 3,
									"outlettype" : [ "", "", "" ],
									"patching_rect" : [ 393.336270779371262, 27.272727012634277, 97.0, 23.0 ],
									"rnbo_classname" : "buffer~",
									"rnbo_extra_attributes" : 									{
										"fill" : "",
										"meta" : "",
										"samplerate" : 0.0,
										"type" : "",
										"file" : "",
										"preset" : 0
									}
,
									"rnbo_serial" : 2,
									"rnbo_uniqueid" : "buffer~_obj-1",
									"rnboinfo" : 									{
										"needsInstanceInfo" : 1,
										"argnames" : 										{
											"info" : 											{
												"attrOrProp" : 1,
												"digest" : "Bang to report buffer information.",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 0,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"touched" : 0,
												"inlet" : 1,
												"type" : "bang"
											}
,
											"sizeout" : 											{
												"attrOrProp" : 1,
												"digest" : "Size in Samples",
												"defaultarg" : 2,
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 0,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"touched" : 0,
												"outlet" : 1,
												"type" : "number",
												"defaultValue" : "0"
											}
,
											"chanout" : 											{
												"attrOrProp" : 1,
												"digest" : "Number of Channels",
												"isalias" : 0,
												"aliases" : [  ],
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"touched" : 0,
												"outlet" : 1,
												"type" : "number",
												"defaultValue" : "0"
											}
,
											"srout" : 											{
												"attrOrProp" : 1,
												"digest" : "Sample rate",
												"isalias" : 0,
												"aliases" : [  ],
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"touched" : 0,
												"outlet" : 1,
												"type" : "number",
												"defaultValue" : "0"
											}
,
											"size" : 											{
												"attrOrProp" : 1,
												"digest" : "Size in Samples. Take care when setting, allocation might block audio processing.",
												"defaultarg" : 2,
												"isalias" : 0,
												"aliases" : [ "samples" ],
												"settable" : 1,
												"attachable" : 1,
												"isparam" : 0,
												"deprecated" : 0,
												"touched" : 0,
												"type" : "number",
												"defaultValue" : "0"
											}
,
											"samples" : 											{
												"attrOrProp" : 1,
												"digest" : "Size in Samples. Take care when setting, allocation might block audio processing.",
												"defaultarg" : 2,
												"isalias" : 1,
												"aliasOf" : "size",
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 1,
												"isparam" : 0,
												"deprecated" : 0,
												"touched" : 0,
												"type" : "number",
												"defaultValue" : "0"
											}
,
											"sizems" : 											{
												"attrOrProp" : 1,
												"digest" : "Size in Milliseconds. Take care when setting, allocation might block audio processing.",
												"isalias" : 0,
												"aliases" : [ "ms" ],
												"settable" : 1,
												"attachable" : 1,
												"isparam" : 0,
												"deprecated" : 0,
												"touched" : 0,
												"type" : "number",
												"defaultValue" : "0"
											}
,
											"ms" : 											{
												"attrOrProp" : 1,
												"digest" : "Size in Milliseconds. Take care when setting, allocation might block audio processing.",
												"isalias" : 1,
												"aliasOf" : "sizems",
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 1,
												"isparam" : 0,
												"deprecated" : 0,
												"touched" : 0,
												"type" : "number",
												"defaultValue" : "0"
											}
,
											"clear" : 											{
												"attrOrProp" : 1,
												"digest" : "Clear the contents of the buffer",
												"isalias" : 0,
												"aliases" : [  ],
												"attachable" : 1,
												"isparam" : 0,
												"deprecated" : 0,
												"touched" : 0,
												"type" : "bang"
											}
,
											"normalize" : 											{
												"attrOrProp" : 1,
												"digest" : "Find Maximum and normalize to the value given.",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 1,
												"isparam" : 0,
												"deprecated" : 0,
												"touched" : 0,
												"type" : "number",
												"defaultValue" : "0.995"
											}
,
											"channels" : 											{
												"attrOrProp" : 1,
												"digest" : "Change channel count. Take care when setting, allocation might block audio processing.",
												"defaultarg" : 3,
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 1,
												"isparam" : 0,
												"deprecated" : 0,
												"touched" : 0,
												"type" : "number",
												"defaultValue" : "1"
											}
,
											"name" : 											{
												"attrOrProp" : 2,
												"digest" : "Name of the data buffer",
												"defaultarg" : 1,
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"touched" : 0,
												"type" : "symbol",
												"mandatory" : 1
											}
,
											"file" : 											{
												"attrOrProp" : 2,
												"digest" : "File name/path or URL to load into buffer.",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"touched" : 0,
												"type" : "symbol"
											}
,
											"type" : 											{
												"attrOrProp" : 2,
												"digest" : "Type of Data (float32, float64)",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"touched" : 0,
												"type" : "symbol"
											}
,
											"samplerate" : 											{
												"attrOrProp" : 2,
												"digest" : "Sample rate",
												"defaultarg" : 4,
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"touched" : 0,
												"type" : "number",
												"defaultValue" : "0"
											}
,
											"fill" : 											{
												"attrOrProp" : 2,
												"digest" : "Fill expression, this could be a value, or a simple function like sin(x), where x will run from 0 to 1 to fill the buffer.",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"touched" : 0,
												"type" : "symbol"
											}
,
											"external" : 											{
												"attrOrProp" : 2,
												"digest" : "Await data from the outside world.",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"touched" : 0,
												"type" : "bool",
												"doNotShowInMaxInspector" : 1
											}
,
											"preset" : 											{
												"attrOrProp" : 2,
												"digest" : "Add this value to the preset.",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"touched" : 0,
												"type" : "bool",
												"defaultValue" : "false",
												"label" : "Include In Preset",
												"category" : "Preset"
											}
,
											"meta" : 											{
												"attrOrProp" : 2,
												"digest" : "A JSON formatted string containing metadata for use by the exported code",
												"isalias" : 0,
												"aliases" : [  ],
												"settable" : 1,
												"attachable" : 0,
												"isparam" : 0,
												"deprecated" : 0,
												"touched" : 0,
												"type" : "symbol",
												"defaultValue" : "",
												"label" : "Metadata"
											}

										}
,
										"inputs" : [ 											{
												"name" : "info",
												"type" : "bang",
												"digest" : "Bang to report buffer information.",
												"hot" : 1,
												"docked" : 0
											}
 ],
										"outputs" : [ 											{
												"name" : "sizeout",
												"type" : "number",
												"digest" : "Size in Samples",
												"defaultarg" : 2,
												"docked" : 0
											}
, 											{
												"name" : "chanout",
												"type" : "number",
												"digest" : "Number of Channels",
												"docked" : 0
											}
, 											{
												"name" : "srout",
												"type" : "number",
												"digest" : "Sample rate",
												"docked" : 0
											}
 ],
										"helpname" : "buffer~",
										"aliasOf" : "data",
										"classname" : "buffer~",
										"operator" : 0,
										"versionId" : 405570163,
										"changesPatcherIO" : 0
									}
,
									"text" : "buffer~ playback"
								}

							}
 ],
						"lines" : [ 							{
								"patchline" : 								{
									"destination" : [ "obj-113", 0 ],
									"midpoints" : [ 480.836270779371262, 51.524145871400833, 479.459646672010422, 51.524145871400833 ],
									"source" : [ "obj-1", 2 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-4", 0 ],
									"midpoints" : [ 441.836270779371262, 48.0, 440.567955255508423, 48.0 ],
									"source" : [ "obj-1", 1 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-6", 0 ],
									"midpoints" : [ 402.836270779371262, 138.0, 402.218441218137741, 138.0 ],
									"source" : [ "obj-1", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-99", 0 ],
									"midpoints" : [ 1610.956288725137711, 297.0, 1610.956288725137711, 297.0 ],
									"source" : [ "obj-100", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-125", 0 ],
									"midpoints" : [ 1492.995125293731689, 360.0, 1492.995125293731689, 360.0 ],
									"source" : [ "obj-102", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-108", 0 ],
									"midpoints" : [ 504.645624279975891, 270.0, 504.645624279975891, 270.0 ],
									"order" : 0,
									"source" : [ "obj-103", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-5", 0 ],
									"midpoints" : [ 504.645624279975891, 270.0, 432.0, 270.0, 432.0, 249.0, 379.888344436883926, 249.0 ],
									"order" : 1,
									"source" : [ "obj-103", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-102", 0 ],
									"midpoints" : [ 1492.995125293731689, 297.0, 1492.995125293731689, 297.0 ],
									"source" : [ "obj-105", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-123", 0 ],
									"midpoints" : [ 1377.946583181619644, 360.0, 1377.946583181619644, 360.0 ],
									"source" : [ "obj-107", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-141", 0 ],
									"midpoints" : [ 626.441744804382324, 342.0, 626.49028280377388, 342.0 ],
									"source" : [ "obj-11", 16 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-36", 0 ],
									"midpoints" : [ 237.379244804382324, 342.0, 232.315530925989151, 342.0 ],
									"source" : [ "obj-11", 1 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-37", 0 ],
									"midpoints" : [ 289.254244804382324, 342.0, 275.519413828849792, 342.0 ],
									"source" : [ "obj-11", 3 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-38", 0 ],
									"midpoints" : [ 263.316744804382324, 342.0, 254.645627707242966, 342.0 ],
									"source" : [ "obj-11", 2 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-39", 0 ],
									"midpoints" : [ 393.004244804382324, 342.0, 361.927179634571075, 342.0 ],
									"source" : [ "obj-11", 7 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-40", 0 ],
									"midpoints" : [ 367.066744804382324, 342.0, 341.053393512964249, 342.0 ],
									"source" : [ "obj-11", 6 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-41", 0 ],
									"midpoints" : [ 341.129244804382324, 342.0, 318.723296731710434, 342.0 ],
									"source" : [ "obj-11", 5 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-42", 0 ],
									"midpoints" : [ 315.191744804382324, 342.0, 297.849510610103607, 342.0 ],
									"source" : [ "obj-11", 4 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-43", 0 ],
									"midpoints" : [ 600.504244804382324, 351.0, 543.0, 351.0, 543.0, 345.0, 532.800963699817657, 345.0 ],
									"source" : [ "obj-11", 15 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-44", 0 ],
									"midpoints" : [ 574.566744804382324, 342.0, 511.927177578210831, 342.0 ],
									"source" : [ "obj-11", 14 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-45", 0 ],
									"midpoints" : [ 548.629244804382324, 342.0, 489.597080796957016, 342.0 ],
									"source" : [ "obj-11", 13 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-46", 0 ],
									"midpoints" : [ 522.691744804382324, 342.0, 468.237857788801193, 342.0 ],
									"source" : [ "obj-11", 12 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-47", 0 ],
									"midpoints" : [ 496.754244804382324, 342.0, 445.907761007547379, 342.0 ],
									"source" : [ "obj-11", 11 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-48", 0 ],
									"midpoints" : [ 211.441744804382324, 342.0, 211.441744804382324, 342.0 ],
									"source" : [ "obj-11", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-49", 0 ],
									"midpoints" : [ 470.816744804382324, 342.0, 426.004848659038544, 342.0 ],
									"source" : [ "obj-11", 10 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-50", 0 ],
									"midpoints" : [ 444.879244804382324, 342.0, 403.189314991235733, 342.0 ],
									"source" : [ "obj-11", 9 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-51", 0 ],
									"midpoints" : [ 418.941744804382324, 342.0, 382.315528869628906, 342.0 ],
									"source" : [ "obj-11", 8 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-14", 0 ],
									"midpoints" : [ 379.888344436883926, 201.0, 379.888344436883926, 201.0 ],
									"source" : [ "obj-111", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-107", 0 ],
									"midpoints" : [ 1377.946583181619644, 297.0, 1377.946583181619644, 297.0 ],
									"source" : [ "obj-112", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-136", 0 ],
									"midpoints" : [ 914.839793413877487, 402.0, 914.839793413877487, 402.0 ],
									"source" : [ "obj-117", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-138", 0 ],
									"midpoints" : [ 123.577668339014053, 90.0, 123.577668339014053, 90.0 ],
									"order" : 2,
									"source" : [ "obj-118", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-4", 0 ],
									"midpoints" : [ 123.577668339014053, 90.0, 249.0, 90.0, 249.0, 114.0, 417.0, 114.0, 417.0, 99.0, 440.567955255508423, 99.0 ],
									"order" : 1,
									"source" : [ "obj-118", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-7", 0 ],
									"midpoints" : [ 123.577668339014053, 90.0, 249.0, 90.0, 249.0, 123.0, 417.0, 123.0, 417.0, 129.0, 559.01455557346344, 129.0 ],
									"order" : 0,
									"source" : [ "obj-118", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-143", 0 ],
									"midpoints" : [ 1029.888335525989532, 402.0, 1029.888335525989532, 402.0 ],
									"source" : [ "obj-120", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-144", 0 ],
									"midpoints" : [ 1147.849498957395554, 402.0, 1147.849498957395554, 402.0 ],
									"source" : [ "obj-121", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-146", 0 ],
									"midpoints" : [ 1262.898041069507599, 402.0, 1262.898041069507599, 402.0 ],
									"source" : [ "obj-122", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-148", 0 ],
									"midpoints" : [ 1377.946583181619644, 402.0, 1377.946583181619644, 402.0 ],
									"source" : [ "obj-123", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-118", 0 ],
									"midpoints" : [ 123.577668339014053, 33.0, 123.577668339014053, 33.0 ],
									"source" : [ "obj-124", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-149", 0 ],
									"midpoints" : [ 1492.995125293731689, 402.0, 1492.995125293731689, 402.0 ],
									"source" : [ "obj-125", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-151", 0 ],
									"midpoints" : [ 1610.956288725137711, 402.0, 1610.956288725137711, 402.0 ],
									"source" : [ "obj-126", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-153", 0 ],
									"midpoints" : [ 1726.004830837249756, 402.0, 1726.004830837249756, 402.0 ],
									"source" : [ "obj-127", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-102", 0 ],
									"midpoints" : [ 810.956299692392349, 363.0, 891.0, 363.0, 891.0, 321.0, 1492.995125293731689, 321.0 ],
									"order" : 2,
									"source" : [ "obj-130", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-107", 0 ],
									"midpoints" : [ 810.956299692392349, 363.0, 891.0, 363.0, 891.0, 321.0, 1377.946583181619644, 321.0 ],
									"order" : 3,
									"source" : [ "obj-130", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-60", 0 ],
									"midpoints" : [ 810.956299692392349, 363.0, 891.0, 363.0, 891.0, 330.0, 914.839793413877487, 330.0 ],
									"order" : 7,
									"source" : [ "obj-130", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-85", 0 ],
									"midpoints" : [ 810.956299692392349, 363.0, 891.0, 363.0, 891.0, 321.0, 1029.888335525989532, 321.0 ],
									"order" : 6,
									"source" : [ "obj-130", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-89", 0 ],
									"midpoints" : [ 810.956299692392349, 363.0, 891.0, 363.0, 891.0, 321.0, 1262.898041069507599, 321.0 ],
									"order" : 4,
									"source" : [ "obj-130", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-92", 0 ],
									"midpoints" : [ 810.956299692392349, 363.0, 891.0, 363.0, 891.0, 321.0, 1147.849498957395554, 321.0 ],
									"order" : 5,
									"source" : [ "obj-130", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-95", 0 ],
									"midpoints" : [ 810.956299692392349, 363.0, 891.0, 363.0, 891.0, 321.0, 1726.004830837249756, 321.0 ],
									"order" : 0,
									"source" : [ "obj-130", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-99", 0 ],
									"midpoints" : [ 810.956299692392349, 363.0, 891.0, 363.0, 891.0, 321.0, 1610.956288725137711, 321.0 ],
									"order" : 1,
									"source" : [ "obj-130", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-170", 0 ],
									"midpoints" : [ 810.956299692392349, 297.0, 810.798693656921387, 297.0 ],
									"source" : [ "obj-131", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-162", 0 ],
									"midpoints" : [ 914.839793413877487, 435.0, 914.839793413877487, 435.0 ],
									"order" : 0,
									"source" : [ "obj-136", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-48", 0 ],
									"midpoints" : [ 914.839793413877487, 435.0, 714.0, 435.0, 714.0, 492.0, 552.0, 492.0, 552.0, 501.0, 186.0, 501.0, 186.0, 345.0, 211.441744804382324, 345.0 ],
									"order" : 1,
									"source" : [ "obj-136", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-103", 0 ],
									"midpoints" : [ 123.577668339014053, 249.0, 480.0, 249.0, 480.0, 240.0, 504.645624279975891, 240.0 ],
									"order" : 0,
									"source" : [ "obj-138", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-15", 0 ],
									"midpoints" : [ 123.577668339014053, 135.0, 189.0, 135.0, 189.0, 123.0, 286.6844622194767, 123.0 ],
									"order" : 1,
									"source" : [ "obj-138", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-103", 0 ],
									"midpoints" : [ 379.888344436883926, 240.0, 504.645624279975891, 240.0 ],
									"source" : [ "obj-14", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-147", 0 ],
									"midpoints" : [ 626.49028280377388, 384.0, 625.519409030675888, 384.0 ],
									"source" : [ "obj-141", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-163", 0 ],
									"midpoints" : [ 1029.888335525989532, 435.0, 1029.888335525989532, 435.0 ],
									"order" : 0,
									"source" : [ "obj-143", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-36", 0 ],
									"midpoints" : [ 1029.888335525989532, 435.0, 1008.0, 435.0, 1008.0, 492.0, 552.0, 492.0, 552.0, 501.0, 240.0, 501.0, 240.0, 345.0, 232.315530925989151, 345.0 ],
									"order" : 1,
									"source" : [ "obj-143", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-165", 0 ],
									"midpoints" : [ 1147.849498957395554, 435.0, 1147.849498957395554, 435.0 ],
									"order" : 0,
									"source" : [ "obj-144", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-38", 0 ],
									"midpoints" : [ 1147.849498957395554, 435.0, 1125.0, 435.0, 1125.0, 492.0, 552.0, 492.0, 552.0, 501.0, 285.0, 501.0, 285.0, 345.0, 254.645627707242966, 345.0 ],
									"order" : 1,
									"source" : [ "obj-144", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-164", 0 ],
									"midpoints" : [ 1262.898041069507599, 435.0, 1262.898041069507599, 435.0 ],
									"order" : 0,
									"source" : [ "obj-146", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-37", 0 ],
									"midpoints" : [ 1262.898041069507599, 435.0, 1242.0, 435.0, 1242.0, 492.0, 552.0, 492.0, 552.0, 501.0, 285.0, 501.0, 285.0, 345.0, 275.519413828849792, 345.0 ],
									"order" : 1,
									"source" : [ "obj-146", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-152", 0 ],
									"midpoints" : [ 662.519409030675888, 432.0, 661.927175521850586, 432.0 ],
									"source" : [ "obj-147", 1 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-166", 0 ],
									"midpoints" : [ 1377.946583181619644, 435.0, 1377.946583181619644, 435.0 ],
									"order" : 0,
									"source" : [ "obj-148", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-42", 0 ],
									"midpoints" : [ 1377.946583181619644, 435.0, 1356.0, 435.0, 1356.0, 492.0, 552.0, 492.0, 552.0, 501.0, 306.0, 501.0, 306.0, 345.0, 297.849510610103607, 345.0 ],
									"order" : 1,
									"source" : [ "obj-148", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-167", 0 ],
									"midpoints" : [ 1492.995125293731689, 435.0, 1492.995125293731689, 435.0 ],
									"order" : 0,
									"source" : [ "obj-149", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-41", 0 ],
									"midpoints" : [ 1492.995125293731689, 435.0, 1473.0, 435.0, 1473.0, 492.0, 552.0, 492.0, 552.0, 501.0, 327.0, 501.0, 327.0, 345.0, 318.723296731710434, 345.0 ],
									"order" : 1,
									"source" : [ "obj-149", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-3", 0 ],
									"midpoints" : [ 286.6844622194767, 189.0, 286.6844622194767, 189.0 ],
									"source" : [ "obj-15", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-168", 0 ],
									"midpoints" : [ 1610.956288725137711, 435.0, 1610.956288725137711, 435.0 ],
									"order" : 0,
									"source" : [ "obj-151", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-40", 0 ],
									"midpoints" : [ 1610.956288725137711, 435.0, 1587.0, 435.0, 1587.0, 480.0, 714.0, 480.0, 714.0, 393.0, 552.0, 393.0, 552.0, 345.0, 341.053393512964249, 345.0 ],
									"order" : 1,
									"source" : [ "obj-151", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-150", 0 ],
									"midpoints" : [ 661.927175521850586, 480.0, 661.927175521850586, 480.0 ],
									"source" : [ "obj-152", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-169", 0 ],
									"midpoints" : [ 1726.004830837249756, 435.0, 1726.004830837249756, 435.0 ],
									"order" : 0,
									"source" : [ "obj-153", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-39", 0 ],
									"midpoints" : [ 1726.004830837249756, 435.0, 1704.0, 435.0, 1704.0, 480.0, 714.0, 480.0, 714.0, 393.0, 552.0, 393.0, 552.0, 345.0, 361.927179634571075, 345.0 ],
									"order" : 1,
									"source" : [ "obj-153", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-159", 0 ],
									"midpoints" : [ 700.276689559221268, 315.0, 700.276689559221268, 315.0 ],
									"source" : [ "obj-157", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-154", 0 ],
									"midpoints" : [ 700.276689559221268, 441.0, 756.5873683989048, 441.0 ],
									"source" : [ "obj-159", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-61", 0 ],
									"midpoints" : [ 914.839793413877487, 471.0, 914.839793413877487, 471.0 ],
									"source" : [ "obj-162", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-84", 0 ],
									"midpoints" : [ 1029.888335525989532, 471.0, 1029.888335525989532, 471.0 ],
									"source" : [ "obj-163", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-88", 0 ],
									"midpoints" : [ 1262.898041069507599, 471.0, 1262.898041069507599, 471.0 ],
									"source" : [ "obj-164", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-91", 0 ],
									"midpoints" : [ 1147.849498957395554, 471.0, 1147.849498957395554, 471.0 ],
									"source" : [ "obj-165", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-106", 0 ],
									"midpoints" : [ 1377.946583181619644, 471.0, 1377.946583181619644, 471.0 ],
									"source" : [ "obj-166", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-101", 0 ],
									"midpoints" : [ 1492.995125293731689, 471.0, 1492.995125293731689, 471.0 ],
									"source" : [ "obj-167", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-98", 0 ],
									"midpoints" : [ 1610.956288725137711, 471.0, 1610.956288725137711, 471.0 ],
									"source" : [ "obj-168", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-94", 0 ],
									"midpoints" : [ 1726.004830837249756, 471.0, 1726.004830837249756, 471.0 ],
									"source" : [ "obj-169", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-11", 0 ],
									"midpoints" : [ 211.92718169093132, 240.0, 211.441744804382324, 240.0 ],
									"source" : [ "obj-17", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-130", 0 ],
									"midpoints" : [ 810.798693656921387, 330.0, 810.956299692392349, 330.0 ],
									"source" : [ "obj-170", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-17", 0 ],
									"midpoints" : [ 211.92718169093132, 162.0, 211.92718169093132, 162.0 ],
									"source" : [ "obj-18", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-11", 0 ],
									"midpoints" : [ 286.6844622194767, 303.0, 211.441744804382324, 303.0 ],
									"source" : [ "obj-29", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-29", 0 ],
									"midpoints" : [ 286.6844622194767, 240.0, 286.6844622194767, 240.0 ],
									"source" : [ "obj-3", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-60", 0 ],
									"midpoints" : [ 914.839793413877487, 297.0, 914.839793413877487, 297.0 ],
									"source" : [ "obj-33", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-20", 0 ],
									"midpoints" : [ 230.265702217817307, 501.0, 243.0, 501.0, 243.0, 534.0, 230.373783379793167, 534.0 ],
									"source" : [ "obj-36", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-52", 0 ],
									"midpoints" : [ 273.469585120677948, 558.0, 297.0, 558.0, 297.0, 594.0, 273.092229396104813, 594.0 ],
									"source" : [ "obj-37", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-54", 0 ],
									"midpoints" : [ 252.595798999071121, 525.0, 273.0, 525.0, 273.0, 567.0, 252.703880161046982, 567.0 ],
									"source" : [ "obj-38", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-63", 0 ],
									"midpoints" : [ 359.877350926399231, 681.0, 372.0, 681.0, 372.0, 723.0, 359.985432088375092, 723.0 ],
									"source" : [ "obj-39", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-15", 1 ],
									"midpoints" : [ 440.567955255508423, 126.0, 317.6844622194767, 126.0 ],
									"order" : 1,
									"source" : [ "obj-4", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-15", 0 ],
									"midpoints" : [ 440.567955255508423, 126.0, 286.6844622194767, 126.0 ],
									"order" : 2,
									"source" : [ "obj-4", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-8", 0 ],
									"midpoints" : [ 440.567955255508423, 126.0, 492.0, 126.0, 492.0, 189.0, 440.567955255508423, 189.0 ],
									"order" : 0,
									"source" : [ "obj-4", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-65", 0 ],
									"midpoints" : [ 339.003564804792404, 651.0, 360.0, 651.0, 360.0, 693.0, 339.111645966768265, 693.0 ],
									"source" : [ "obj-40", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-66", 0 ],
									"midpoints" : [ 316.673468023538589, 618.0, 339.0, 618.0, 339.0, 657.0, 316.78154918551445, 657.0 ],
									"source" : [ "obj-41", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-68", 0 ],
									"midpoints" : [ 295.799681901931763, 588.0, 306.0, 588.0, 306.0, 624.0, 295.907763063907623, 624.0 ],
									"source" : [ "obj-42", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-75", 0 ],
									"midpoints" : [ 530.751134991645813, 894.0, 549.0, 894.0, 549.0, 963.0, 530.859216153621674, 963.0 ],
									"source" : [ "obj-43", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-77", 0 ],
									"midpoints" : [ 509.877348870038986, 861.0, 528.0, 861.0, 528.0, 933.0, 509.499993145465851, 933.0 ],
									"source" : [ "obj-44", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-78", 0 ],
									"midpoints" : [ 487.547252088785172, 834.0, 516.0, 834.0, 516.0, 900.0, 487.169896364212036, 900.0 ],
									"source" : [ "obj-45", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-80", 0 ],
									"midpoints" : [ 466.188029080629349, 801.0, 486.0, 801.0, 486.0, 873.0, 466.296110242605209, 873.0 ],
									"source" : [ "obj-46", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-69", 0 ],
									"midpoints" : [ 443.857932299375534, 771.0, 474.0, 771.0, 474.0, 843.0, 443.966013461351395, 843.0 ],
									"source" : [ "obj-47", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-56", 0 ],
									"midpoints" : [ 209.39191609621048, 492.0, 209.49999725818634, 492.0 ],
									"source" : [ "obj-48", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-71", 0 ],
									"midpoints" : [ 423.955019950866699, 771.0, 441.0, 771.0, 441.0, 810.0, 423.577664226293564, 810.0 ],
									"source" : [ "obj-49", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-11", 0 ],
									"midpoints" : [ 379.888344436883926, 303.0, 211.441744804382324, 303.0 ],
									"source" : [ "obj-5", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-72", 0 ],
									"midpoints" : [ 401.139486283063889, 714.0, 393.0, 714.0, 393.0, 753.0, 366.0, 753.0, 366.0, 783.0, 401.247567445039749, 783.0 ],
									"source" : [ "obj-50", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-74", 0 ],
									"midpoints" : [ 380.265700161457062, 681.0, 393.0, 681.0, 393.0, 753.0, 380.373781323432922, 753.0 ],
									"source" : [ "obj-51", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-157", 0 ],
									"midpoints" : [ 402.218441218137741, 174.0, 534.0, 174.0, 534.0, 231.0, 700.276689559221268, 231.0 ],
									"source" : [ "obj-6", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-117", 0 ],
									"midpoints" : [ 914.839793413877487, 360.0, 914.839793413877487, 360.0 ],
									"source" : [ "obj-60", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-120", 0 ],
									"midpoints" : [ 1029.888335525989532, 360.0, 1029.888335525989532, 360.0 ],
									"source" : [ "obj-85", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-85", 0 ],
									"midpoints" : [ 1029.888335525989532, 297.0, 1029.888335525989532, 297.0 ],
									"source" : [ "obj-86", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-122", 0 ],
									"midpoints" : [ 1262.898041069507599, 360.0, 1262.898041069507599, 360.0 ],
									"source" : [ "obj-89", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-111", 0 ],
									"midpoints" : [ 211.92718169093132, 123.0, 379.888344436883926, 123.0 ],
									"order" : 0,
									"source" : [ "obj-9", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-18", 0 ],
									"midpoints" : [ 211.92718169093132, 60.0, 211.92718169093132, 60.0 ],
									"order" : 2,
									"source" : [ "obj-9", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-97", 0 ],
									"midpoints" : [ 211.92718169093132, 78.524145871400833, 274.264843434095383, 78.524145871400833 ],
									"order" : 1,
									"source" : [ "obj-9", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-89", 0 ],
									"midpoints" : [ 1262.898041069507599, 297.0, 1262.898041069507599, 297.0 ],
									"source" : [ "obj-90", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-121", 0 ],
									"midpoints" : [ 1147.849498957395554, 360.0, 1147.849498957395554, 360.0 ],
									"source" : [ "obj-92", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-92", 0 ],
									"midpoints" : [ 1147.849498957395554, 297.0, 1147.849498957395554, 297.0 ],
									"source" : [ "obj-93", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-127", 0 ],
									"midpoints" : [ 1726.004830837249756, 360.0, 1726.004830837249756, 360.0 ],
									"source" : [ "obj-95", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-95", 0 ],
									"midpoints" : [ 1726.004830837249756, 297.0, 1726.004830837249756, 297.0 ],
									"source" : [ "obj-96", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-7", 0 ],
									"midpoints" : [ 274.264843434095383, 123.0, 417.0, 123.0, 417.0, 129.0, 559.01455557346344, 129.0 ],
									"source" : [ "obj-97", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-126", 0 ],
									"midpoints" : [ 1610.956288725137711, 360.0, 1610.956288725137711, 360.0 ],
									"source" : [ "obj-99", 0 ]
								}

							}
 ]
					}
,
					"patching_rect" : [ 680.0, 257.0, 187.0, 35.0 ],
					"rnboattrcache" : 					{

					}
,
					"rnboversion" : "1.4.4",
					"saved_attribute_attributes" : 					{
						"valueof" : 						{
							"parameter_invisible" : 1,
							"parameter_longname" : "rnbo~",
							"parameter_modmode" : 0,
							"parameter_shortname" : "rnbo~",
							"parameter_type" : 3
						}

					}
,
					"saved_object_attributes" : 					{
						"optimization" : "O1",
						"parameter_enable" : 1,
						"uuid" : "d65e8293-b6d4-11f1-8293-9201e65fa3fa"
					}
,
					"snapshot" : 					{
						"filetype" : "C74Snapshot",
						"version" : 2,
						"minorversion" : 0,
						"name" : "snapshotlist",
						"origin" : "rnbo~",
						"type" : "list",
						"subtype" : "Undefined",
						"embed" : 1,
						"snapshot" : 						{
							"__presetid" : "d65e8293-b6d4-11f1-8293-9201e65fa3fa"
						}
,
						"snapshotlist" : 						{
							"current_snapshot" : 0,
							"entries" : [ 								{
									"filetype" : "C74Snapshot",
									"version" : 2,
									"minorversion" : 0,
									"name" : "untitled",
									"origin" : "d65e8293-b6d4-11f1-8293-9201e65fa3fa",
									"type" : "rnbo",
									"subtype" : "",
									"embed" : 0,
									"snapshot" : 									{
										"__presetid" : "d65e8293-b6d4-11f1-8293-9201e65fa3fa"
									}
,
									"fileref" : 									{
										"name" : "untitled",
										"filename" : "untitled_20260922.maxsnap",
										"filepath" : "~/Documents/Max 9/Snapshots",
										"filepos" : -1,
										"snapshotfileid" : "03d2f3c2530ec9b82e88baec5f658945"
									}

								}
 ]
						}

					}
,
					"text" : "rnbo~ @name playerMultichannel",
					"varname" : "rnbo~"
				}

			}
 ],
		"lines" : [  ],
		"parameters" : 		{
			"obj-1" : [ "rnbo~", "rnbo~", 0 ],
			"parameterbanks" : 			{
				"0" : 				{
					"index" : 0,
					"name" : "",
					"parameters" : [ "-", "-", "-", "-", "-", "-", "-", "-" ]
				}

			}
,
			"inherited_shortname" : 1
		}
,
		"dependency_cache" : [ 			{
				"name" : "UniversosParalelos.wav",
				"bootpath" : "~/Music",
				"patcherrelativepath" : "../../../../Music",
				"type" : "WAVE",
				"implicit" : 1
			}
, 			{
				"name" : "untitled_20260922.maxsnap",
				"bootpath" : "~/Documents/Max 9/Snapshots",
				"patcherrelativepath" : "../../../Max 9/Snapshots",
				"type" : "mx@s",
				"implicit" : 1
			}
 ],
		"autosave" : 0
	}

}
