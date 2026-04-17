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
		"rect" : [ 34.0, 191.0, 1000.0, 755.0 ],
		"default_fontsize" : 11.0,
		"gridonopen" : 2,
		"gridsize" : [ 10.0, 10.0 ],
		"gridsnaponopen" : 2,
		"toolbarvisible" : 0,
		"boxes" : [ 			{
				"box" : 				{
					"hidden" : 1,
					"id" : "obj-2",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 1015.0, 675.0, 83.0, 21.0 ],
					"saved_object_attributes" : 					{
						"filename" : "spat5.style.js",
						"parameter_enable" : 0
					}
,
					"text" : "js spat5.style.js"
				}

			}
, 			{
				"box" : 				{
					"args" : [ "spat5.tuto-basic-3", "maxpat" ],
					"bgmode" : 0,
					"border" : 0,
					"clickthrough" : 0,
					"enablehscroll" : 0,
					"enablevscroll" : 0,
					"id" : "obj-48",
					"lockeddragscroll" : 0,
					"lockedsize" : 0,
					"maxclass" : "bpatcher",
					"name" : "spat5.openpatcher.maxpat",
					"numinlets" : 0,
					"numoutlets" : 0,
					"offset" : [ 0.0, 0.0 ],
					"patching_rect" : [ 262.0, 72.5, 170.0, 20.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 28.25, 185.0, 170.0, 20.0 ],
					"viewvisibility" : 1
				}

			}
, 			{
				"box" : 				{
					"bubble" : 1,
					"bubbleside" : 0,
					"fontname" : "Arial",
					"fontsize" : 11.0,
					"id" : "obj-47",
					"linecount" : 3,
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 75.75, 314.5, 162.0, 62.0 ],
					"presentation_linecount" : 3,
					"saved_attribute_attributes" : 					{
						"bubble_bgcolor" : 						{
							"expression" : "themecolor.theme_bubble_bgcolor"
						}
,
						"bubble_outlinecolor" : 						{
							"expression" : "themecolor.theme_bubble_outlinecolor"
						}
,
						"textcolor" : 						{
							"expression" : "themecolor.live_control_fg"
						}

					}
,
					"text" : "bpatcher spat5.input~.maxpat (an abstraction shipped with the Spat5 package)",
					"textjustification" : 1
				}

			}
, 			{
				"box" : 				{
					"bubble" : 1,
					"fontname" : "Arial",
					"fontsize" : 11.0,
					"id" : "obj-46",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 751.5, 731.0, 161.0, 23.0 ],
					"saved_attribute_attributes" : 					{
						"bubble_bgcolor" : 						{
							"expression" : "themecolor.theme_bubble_bgcolor"
						}
,
						"bubble_outlinecolor" : 						{
							"expression" : "themecolor.theme_bubble_outlinecolor"
						}
,
						"textcolor" : 						{
							"expression" : "themecolor.live_control_fg"
						}

					}
,
					"text" : "measured RMS levels in dB"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-44",
					"maxclass" : "spat5.osc.view",
					"numinlets" : 1,
					"numoutlets" : 3,
					"outlettype" : [ "", "int", "" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 255.0, 729.0, 500.0, 25.0 ]
				}

			}
, 			{
				"box" : 				{
					"bubble" : 1,
					"fontname" : "Arial",
					"fontsize" : 11.0,
					"id" : "obj-43",
					"linecount" : 8,
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 725.0, 619.0, 118.0, 109.0 ],
					"presentation_linecount" : 8,
					"saved_attribute_attributes" : 					{
						"bubble_bgcolor" : 						{
							"expression" : "themecolor.theme_bubble_bgcolor"
						}
,
						"bubble_outlinecolor" : 						{
							"expression" : "themecolor.theme_bubble_outlinecolor"
						}
,
						"textcolor" : 						{
							"expression" : "themecolor.live_control_fg"
						}

					}
,
					"text" : "this \"upward\" message contains the RMS level of the loudspeakers. It is used to display the vumeters in spat5.oper"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-22",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "" ],
					"patching_rect" : [ 255.0, 695.0, 152.0, 21.0 ],
					"text" : "spat5.osc.prepend /speakers"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-42",
					"maxclass" : "newobj",
					"numinlets" : 16,
					"numoutlets" : 2,
					"outlettype" : [ "", "" ],
					"patching_rect" : [ 255.0, 665.0, 176.5, 21.0 ],
					"saved_object_attributes" : 					{
						"parameter_enable" : 0
					}
,
					"text" : "spat5.rms~ @channels 16"
				}

			}
, 			{
				"box" : 				{
					"bubble" : 1,
					"bubbleside" : 0,
					"fontname" : "Arial",
					"fontsize" : 11.0,
					"id" : "obj-41",
					"linecount" : 2,
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 555.0, 525.0, 126.0, 50.0 ],
					"presentation_linecount" : 2,
					"saved_attribute_attributes" : 					{
						"bubble_bgcolor" : 						{
							"expression" : "themecolor.theme_bubble_bgcolor"
						}
,
						"bubble_outlinecolor" : 						{
							"expression" : "themecolor.theme_bubble_outlinecolor"
						}
,
						"textcolor" : 						{
							"expression" : "themecolor.live_control_fg"
						}

					}
,
					"text" : "create an equalizer for the loudspeakers",
					"textjustification" : 1
				}

			}
, 			{
				"box" : 				{
					"bubble" : 1,
					"fontname" : "Arial",
					"fontsize" : 11.0,
					"id" : "obj-40",
					"linecount" : 4,
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 281.75, 525.0, 149.0, 60.0 ],
					"presentation_linecount" : 4,
					"saved_attribute_attributes" : 					{
						"bubble_bgcolor" : 						{
							"expression" : "themecolor.theme_bubble_bgcolor"
						}
,
						"bubble_outlinecolor" : 						{
							"expression" : "themecolor.theme_bubble_outlinecolor"
						}
,
						"textcolor" : 						{
							"expression" : "themecolor.live_control_fg"
						}

					}
,
					"text" : "apply equalization to the speakers (here, same kind of EQ for the 8 loudspeakers)"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-39",
					"maxclass" : "newobj",
					"numinlets" : 16,
					"numoutlets" : 17,
					"outlettype" : [ "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "" ],
					"patching_rect" : [ 33.75, 545.0, 246.428573999999998, 21.0 ],
					"saved_object_attributes" : 					{
						"parameter_enable" : 0
					}
,
					"text" : "spat5.cascade~ @channels 16"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-37",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 575.0, 474.0, 111.0, 21.0 ],
					"text" : "/window/openorclose"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-15",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 3,
					"outlettype" : [ "", "", "" ],
					"patching_rect" : [ 575.0, 501.0, 83.0, 21.0 ],
					"saved_object_attributes" : 					{
						"parameter_enable" : 0
					}
,
					"text" : "spat5.equalizer",
					"varname" : "spat5.equalizer"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-36",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 678.0, 243.5, 29.0, 21.0 ],
					"text" : "thru"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-35",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 885.0, 195.0, 97.0, 21.0 ],
					"text" : "/source/2/azim $1"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-34",
					"maxclass" : "newobj",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "float" ],
					"patching_rect" : [ 885.0, 170.0, 33.0, 21.0 ],
					"text" : "+ 30."
				}

			}
, 			{
				"box" : 				{
					"bubble" : 1,
					"fontname" : "Arial",
					"fontsize" : 11.0,
					"id" : "obj-25",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 281.75, 474.0, 252.0, 23.0 ],
					"saved_attribute_attributes" : 					{
						"bubble_bgcolor" : 						{
							"expression" : "themecolor.theme_bubble_bgcolor"
						}
,
						"bubble_outlinecolor" : 						{
							"expression" : "themecolor.theme_bubble_outlinecolor"
						}
,
						"textcolor" : 						{
							"expression" : "themecolor.live_control_fg"
						}

					}
,
					"text" : "compensate for varying loudspeaker distances"
				}

			}
, 			{
				"box" : 				{
					"bubble" : 1,
					"fontname" : "Arial",
					"fontsize" : 11.0,
					"id" : "obj-24",
					"linecount" : 3,
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 655.0, 402.0, 126.0, 47.0 ],
					"presentation_linecount" : 3,
					"saved_attribute_attributes" : 					{
						"bubble_bgcolor" : 						{
							"expression" : "themecolor.theme_bubble_bgcolor"
						}
,
						"bubble_outlinecolor" : 						{
							"expression" : "themecolor.theme_bubble_outlinecolor"
						}
,
						"textcolor" : 						{
							"expression" : "themecolor.live_control_fg"
						}

					}
,
					"text" : "forward the speaker positions to spat5.align~"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-14",
					"maxclass" : "newobj",
					"numinlets" : 16,
					"numoutlets" : 17,
					"outlettype" : [ "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "" ],
					"patching_rect" : [ 33.75, 475.0, 187.0, 21.0 ],
					"saved_object_attributes" : 					{
						"parameter_enable" : 0
					}
,
					"text" : "spat5.align~ @speakers 16"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-8",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 775.0, 22.0, 65.0, 21.0 ],
					"text" : "loadmess 1"
				}

			}
, 			{
				"box" : 				{
					"bubble" : 1,
					"bubbleside" : 2,
					"id" : "obj-7",
					"linecount" : 4,
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 555.0, 216.5, 100.0, 75.0 ],
					"presentation_linecount" : 4,
					"saved_attribute_attributes" : 					{
						"bubble_bgcolor" : 						{
							"expression" : "themecolor.theme_bubble_bgcolor"
						}
,
						"bubble_outlinecolor" : 						{
							"expression" : "themecolor.theme_bubble_outlinecolor"
						}
,
						"textcolor" : 						{
							"expression" : "themecolor.live_control_fg"
						}

					}
,
					"text" : "it is possible to compare various panning algorithms",
					"textjustification" : 1
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-32",
					"maxclass" : "live.tab",
					"num_lines_patching" : 1,
					"num_lines_presentation" : 0,
					"numinlets" : 1,
					"numoutlets" : 3,
					"outlettype" : [ "", "", "float" ],
					"parameter_enable" : 1,
					"patching_rect" : [ 495.0, 294.0, 139.5, 20.0 ],
					"saved_attribute_attributes" : 					{
						"valueof" : 						{
							"parameter_enum" : [ "vbap2d", "aep2d", "angular" ],
							"parameter_longname" : "live.tab[1]",
							"parameter_mmax" : 2,
							"parameter_modmode" : 0,
							"parameter_shortname" : "live.tab[1]",
							"parameter_type" : 2,
							"parameter_unitstyle" : 9
						}

					}
,
					"varname" : "live.tab"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-26",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "bang" ],
					"patching_rect" : [ 645.0, 35.0, 54.0, 21.0 ],
					"text" : "loadbang"
				}

			}
, 			{
				"box" : 				{
					"bubble" : 1,
					"bubbleside" : 2,
					"id" : "obj-16",
					"linecount" : 2,
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 923.5, 226.5, 150.0, 50.0 ],
					"presentation_linecount" : 2,
					"saved_attribute_attributes" : 					{
						"bubble_bgcolor" : 						{
							"expression" : "themecolor.theme_bubble_bgcolor"
						}
,
						"bubble_outlinecolor" : 						{
							"expression" : "themecolor.theme_bubble_outlinecolor"
						}
,
						"textcolor" : 						{
							"expression" : "themecolor.live_control_fg"
						}

					}
,
					"text" : "bpatcher spat5.gui.control.maxpat",
					"textjustification" : 1
				}

			}
, 			{
				"box" : 				{
					"bubble" : 1,
					"bubbleside" : 2,
					"id" : "obj-3",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 763.0, 246.5, 138.0, 38.0 ],
					"saved_attribute_attributes" : 					{
						"bubble_bgcolor" : 						{
							"expression" : "themecolor.theme_bubble_bgcolor"
						}
,
						"bubble_outlinecolor" : 						{
							"expression" : "themecolor.theme_bubble_outlinecolor"
						}
,
						"textcolor" : 						{
							"expression" : "themecolor.live_control_fg"
						}

					}
,
					"text" : "click here to open the GUI"
				}

			}
, 			{
				"box" : 				{
					"bgmode" : 0,
					"border" : 0,
					"clickthrough" : 0,
					"enablehscroll" : 0,
					"enablevscroll" : 0,
					"id" : "obj-76",
					"lockeddragscroll" : 0,
					"lockedsize" : 0,
					"maxclass" : "bpatcher",
					"name" : "spat5.gui.control.maxpat",
					"numinlets" : 1,
					"numoutlets" : 1,
					"offset" : [ 0.0, 0.0 ],
					"outlettype" : [ "" ],
					"patching_rect" : [ 795.0, 275.0, 293.0, 41.0 ],
					"viewvisibility" : 1
				}

			}
, 			{
				"box" : 				{
					"fontface" : 1,
					"fontsize" : 14.0,
					"id" : "obj-5",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 25.0, 25.0, 543.0, 22.0 ],
					"saved_attribute_attributes" : 					{
						"bubble_bgcolor" : 						{
							"expression" : "themecolor.theme_bubble_bgcolor"
						}
,
						"bubble_outlinecolor" : 						{
							"expression" : "themecolor.theme_bubble_outlinecolor"
						}
,
						"textcolor" : 						{
							"expression" : "themecolor.live_control_fg"
						}

					}
,
					"text" : "Example : 2 mono sources to 8 loudspeakers outputs + alignment + equalization"
				}

			}
, 			{
				"box" : 				{
					"bubble" : 1,
					"fontname" : "Arial",
					"fontsize" : 11.0,
					"id" : "obj-1",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 709.0, 335.0, 125.0, 23.0 ],
					"saved_attribute_attributes" : 					{
						"bubble_bgcolor" : 						{
							"expression" : "themecolor.theme_bubble_bgcolor"
						}
,
						"bubble_outlinecolor" : 						{
							"expression" : "themecolor.theme_bubble_outlinecolor"
						}
,
						"textcolor" : 						{
							"expression" : "themecolor.live_control_fg"
						}

					}
,
					"text" : "double-click to open"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-38",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 775.0, 195.0, 97.0, 21.0 ],
					"text" : "/source/1/azim $1"
				}

			}
, 			{
				"box" : 				{
					"bgmode" : 0,
					"border" : 0,
					"clickthrough" : 0,
					"enablehscroll" : 0,
					"enablevscroll" : 0,
					"id" : "obj-33",
					"lockeddragscroll" : 0,
					"lockedsize" : 0,
					"maxclass" : "bpatcher",
					"name" : "spat5.around.maxpat",
					"numinlets" : 1,
					"numoutlets" : 1,
					"offset" : [ 0.0, 0.0 ],
					"outlettype" : [ "" ],
					"patching_rect" : [ 871.874916851520538, 55.624994695186615, 130.0, 110.0 ],
					"viewvisibility" : 1
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-27",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 247.0, 170.0, 132.0, 21.0 ],
					"text" : "/title \"Source 2\", /gain -20"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-30",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "bang" ],
					"patching_rect" : [ 247.0, 141.0, 54.0, 21.0 ],
					"text" : "loadbang"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-23",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 35.0, 171.0, 132.0, 21.0 ],
					"text" : "/title \"Source 1\", /gain -30"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-19",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "bang" ],
					"patching_rect" : [ 35.0, 141.0, 56.0, 21.0 ],
					"text" : "loadbang"
				}

			}
, 			{
				"box" : 				{
					"bgmode" : 0,
					"border" : 0,
					"clickthrough" : 0,
					"enablehscroll" : 0,
					"enablevscroll" : 0,
					"id" : "obj-9",
					"lockeddragscroll" : 0,
					"lockedsize" : 0,
					"maxclass" : "bpatcher",
					"name" : "spat5.input~.maxpat",
					"numinlets" : 1,
					"numoutlets" : 1,
					"offset" : [ 0.0, 0.0 ],
					"outlettype" : [ "signal" ],
					"patching_rect" : [ 247.0, 201.0, 210.0, 121.0 ],
					"viewvisibility" : 1
				}

			}
, 			{
				"box" : 				{
					"bubble" : 1,
					"bubbleside" : 3,
					"id" : "obj-6",
					"linecount" : 3,
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 25.0, 59.0, 235.0, 47.0 ],
					"presentation_linecount" : 3,
					"saved_attribute_attributes" : 					{
						"bubble_bgcolor" : 						{
							"expression" : "themecolor.theme_bubble_bgcolor"
						}
,
						"bubble_outlinecolor" : 						{
							"expression" : "themecolor.theme_bubble_outlinecolor"
						}
,
						"textcolor" : 						{
							"expression" : "themecolor.live_control_fg"
						}

					}
,
					"text" : "This tutorial is a follow-up on the previous tutorial. It serves similar purpose, but goes one step further"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-28",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 495.0, 265.0, 65.0, 21.0 ],
					"text" : "loadmess 0"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-31",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 495.0, 335.0, 90.0, 21.0 ],
					"text" : "/panning/type $1"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-45",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 645.0, 375.0, 29.0, 21.0 ],
					"text" : "thru"
				}

			}
, 			{
				"box" : 				{
					"bgmode" : 0,
					"border" : 0,
					"clickthrough" : 0,
					"enablehscroll" : 0,
					"enablevscroll" : 0,
					"id" : "obj-29",
					"lockeddragscroll" : 0,
					"lockedsize" : 0,
					"maxclass" : "bpatcher",
					"name" : "spat5.monitor.maxpat",
					"numinlets" : 1,
					"numoutlets" : 0,
					"offset" : [ 0.0, 0.0 ],
					"patching_rect" : [ 735.0, 465.0, 380.0, 135.0 ],
					"viewvisibility" : 1
				}

			}
, 			{
				"box" : 				{
					"bgcolor" : [ 1.0, 1.0, 1.0, 0.0 ],
					"bgmode" : 0,
					"border" : 0,
					"clickthrough" : 0,
					"enablehscroll" : 0,
					"enablevscroll" : 0,
					"id" : "obj-60",
					"lockeddragscroll" : 0,
					"lockedsize" : 0,
					"maxclass" : "bpatcher",
					"name" : "spat5.copyright.maxpat",
					"numinlets" : 0,
					"numoutlets" : 0,
					"offset" : [ 0.0, 0.0 ],
					"patching_rect" : [ 876.0, 602.0, 239.0, 70.0 ],
					"viewvisibility" : 1
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-18",
					"maxclass" : "newobj",
					"numinlets" : 16,
					"numoutlets" : 0,
					"patching_rect" : [ 33.749998000000005, 695.0, 221.0, 21.0 ],
					"text" : "dac~ 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16"
				}

			}
, 			{
				"box" : 				{
					"channels" : 16,
					"focusbordercolor" : [ 0.0, 0.019608, 0.078431, 0.0 ],
					"id" : "obj-12",
					"lastchannelcount" : 0,
					"maxclass" : "live.gain~",
					"numinlets" : 16,
					"numoutlets" : 19,
					"outlettype" : [ "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "", "float", "list" ],
					"parameter_enable" : 1,
					"patching_rect" : [ 33.750001999999995, 575.0, 218.0, 70.0 ],
					"relative" : 1,
					"saved_attribute_attributes" : 					{
						"focusbordercolor" : 						{
							"expression" : ""
						}
,
						"valueof" : 						{
							"parameter_initial" : [ 0.0 ],
							"parameter_longname" : "live.gain~[3]",
							"parameter_mmax" : 6.0,
							"parameter_mmin" : -70.0,
							"parameter_modmode" : 0,
							"parameter_shortname" : "loudspeakers",
							"parameter_type" : 0,
							"parameter_unitstyle" : 4
						}

					}
,
					"varname" : "live.gain~"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-11",
					"maxclass" : "newobj",
					"numinlets" : 2,
					"numoutlets" : 17,
					"outlettype" : [ "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "" ],
					"patching_rect" : [ 35.0, 415.0, 238.0, 21.0 ],
					"saved_object_attributes" : 					{
						"parameter_enable" : 0
					}
,
					"text" : "spat5.spat~ @inputs 2 @outputs 16 @rooms 1"
				}

			}
, 			{
				"box" : 				{
					"bgmode" : 0,
					"border" : 0,
					"clickthrough" : 0,
					"enablehscroll" : 0,
					"enablevscroll" : 0,
					"id" : "obj-17",
					"lockeddragscroll" : 0,
					"lockedsize" : 0,
					"maxclass" : "bpatcher",
					"name" : "spat5.input~.maxpat",
					"numinlets" : 1,
					"numoutlets" : 1,
					"offset" : [ 0.0, 0.0 ],
					"outlettype" : [ "signal" ],
					"patching_rect" : [ 35.0, 201.0, 210.0, 121.0 ],
					"viewvisibility" : 1
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-13",
					"linecount" : 5,
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 644.999938488006592, 65.0, 198.749981045722961, 70.0 ],
					"presentation_linecount" : 5,
					"text" : "/source/number 2, /speaker/number 16, /speakers/xy 0 2 1 2 1 0 1 -2 0 -2 -1 -2 -1 0 -1 2, /source/2/color 0 0 0.5 0.75, /speaker/*/vumeter/visible 1, bang"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-10",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 4,
					"outlettype" : [ "", "", "", "" ],
					"patching_rect" : [ 645.0, 335.0, 62.0, 21.0 ],
					"saved_object_attributes" : 					{
						"parameter_enable" : 0
					}
,
					"text" : "spat5.oper",
					"varname" : "spat5.viewer"
				}

			}
 ],
		"lines" : [ 			{
				"patchline" : 				{
					"destination" : [ "obj-45", 0 ],
					"source" : [ "obj-10", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-14", 15 ],
					"source" : [ "obj-11", 15 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-14", 14 ],
					"source" : [ "obj-11", 14 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-14", 13 ],
					"source" : [ "obj-11", 13 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-14", 12 ],
					"source" : [ "obj-11", 12 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-14", 11 ],
					"source" : [ "obj-11", 11 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-14", 10 ],
					"source" : [ "obj-11", 10 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-14", 9 ],
					"source" : [ "obj-11", 9 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-14", 8 ],
					"source" : [ "obj-11", 8 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-14", 7 ],
					"source" : [ "obj-11", 7 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-14", 6 ],
					"source" : [ "obj-11", 6 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-14", 5 ],
					"source" : [ "obj-11", 5 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-14", 4 ],
					"source" : [ "obj-11", 4 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-14", 3 ],
					"source" : [ "obj-11", 3 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-14", 2 ],
					"source" : [ "obj-11", 2 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-14", 1 ],
					"source" : [ "obj-11", 1 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-14", 0 ],
					"source" : [ "obj-11", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-18", 15 ],
					"order" : 1,
					"source" : [ "obj-12", 15 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-18", 14 ],
					"order" : 1,
					"source" : [ "obj-12", 14 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-18", 13 ],
					"order" : 1,
					"source" : [ "obj-12", 13 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-18", 12 ],
					"order" : 1,
					"source" : [ "obj-12", 12 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-18", 11 ],
					"order" : 1,
					"source" : [ "obj-12", 11 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-18", 10 ],
					"order" : 1,
					"source" : [ "obj-12", 10 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-18", 9 ],
					"order" : 1,
					"source" : [ "obj-12", 9 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-18", 8 ],
					"order" : 1,
					"source" : [ "obj-12", 8 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-18", 7 ],
					"order" : 1,
					"source" : [ "obj-12", 7 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-18", 6 ],
					"order" : 1,
					"source" : [ "obj-12", 6 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-18", 5 ],
					"order" : 1,
					"source" : [ "obj-12", 5 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-18", 4 ],
					"order" : 1,
					"source" : [ "obj-12", 4 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-18", 3 ],
					"order" : 1,
					"source" : [ "obj-12", 3 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-18", 2 ],
					"order" : 1,
					"source" : [ "obj-12", 2 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-18", 1 ],
					"order" : 1,
					"source" : [ "obj-12", 1 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-18", 0 ],
					"order" : 1,
					"source" : [ "obj-12", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-42", 15 ],
					"order" : 0,
					"source" : [ "obj-12", 15 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-42", 14 ],
					"order" : 0,
					"source" : [ "obj-12", 14 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-42", 13 ],
					"order" : 0,
					"source" : [ "obj-12", 13 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-42", 12 ],
					"order" : 0,
					"source" : [ "obj-12", 12 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-42", 11 ],
					"order" : 0,
					"source" : [ "obj-12", 11 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-42", 10 ],
					"order" : 0,
					"source" : [ "obj-12", 10 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-42", 9 ],
					"order" : 0,
					"source" : [ "obj-12", 9 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-42", 8 ],
					"order" : 0,
					"source" : [ "obj-12", 8 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-42", 7 ],
					"order" : 0,
					"source" : [ "obj-12", 7 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-42", 6 ],
					"order" : 0,
					"source" : [ "obj-12", 6 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-42", 5 ],
					"order" : 0,
					"source" : [ "obj-12", 5 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-42", 4 ],
					"order" : 0,
					"source" : [ "obj-12", 4 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-42", 3 ],
					"order" : 0,
					"source" : [ "obj-12", 3 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-42", 2 ],
					"order" : 0,
					"source" : [ "obj-12", 2 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-42", 1 ],
					"order" : 0,
					"source" : [ "obj-12", 1 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-42", 0 ],
					"order" : 0,
					"source" : [ "obj-12", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-10", 0 ],
					"source" : [ "obj-13", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-39", 15 ],
					"source" : [ "obj-14", 15 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-39", 14 ],
					"source" : [ "obj-14", 14 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-39", 13 ],
					"source" : [ "obj-14", 13 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-39", 12 ],
					"source" : [ "obj-14", 12 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-39", 11 ],
					"source" : [ "obj-14", 11 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-39", 10 ],
					"source" : [ "obj-14", 10 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-39", 9 ],
					"source" : [ "obj-14", 9 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-39", 8 ],
					"source" : [ "obj-14", 8 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-39", 7 ],
					"source" : [ "obj-14", 7 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-39", 6 ],
					"source" : [ "obj-14", 6 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-39", 5 ],
					"source" : [ "obj-14", 5 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-39", 4 ],
					"source" : [ "obj-14", 4 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-39", 3 ],
					"source" : [ "obj-14", 3 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-39", 2 ],
					"source" : [ "obj-14", 2 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-39", 1 ],
					"source" : [ "obj-14", 1 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-39", 0 ],
					"source" : [ "obj-14", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-39", 0 ],
					"midpoints" : [ 584.5, 533.0, 43.25, 533.0 ],
					"source" : [ "obj-15", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-11", 0 ],
					"source" : [ "obj-17", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-23", 0 ],
					"source" : [ "obj-19", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-10", 0 ],
					"midpoints" : [ 264.5, 723.0, 721.5, 723.0, 721.5, 324.0, 654.5, 324.0 ],
					"order" : 0,
					"source" : [ "obj-22", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-44", 0 ],
					"order" : 1,
					"source" : [ "obj-22", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-17", 0 ],
					"source" : [ "obj-23", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-13", 0 ],
					"source" : [ "obj-26", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-9", 0 ],
					"source" : [ "obj-27", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-32", 0 ],
					"source" : [ "obj-28", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-27", 0 ],
					"source" : [ "obj-30", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-45", 0 ],
					"midpoints" : [ 504.5, 370.0, 654.5, 370.0 ],
					"source" : [ "obj-31", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-31", 0 ],
					"midpoints" : [ 564.75, 324.0, 504.5, 324.0 ],
					"source" : [ "obj-32", 1 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-34", 0 ],
					"midpoints" : [ 881.374916851520538, 162.0, 894.5, 162.0 ],
					"order" : 0,
					"source" : [ "obj-33", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-38", 0 ],
					"order" : 1,
					"source" : [ "obj-33", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-35", 0 ],
					"source" : [ "obj-34", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-36", 0 ],
					"midpoints" : [ 894.5, 229.25, 687.5, 229.25 ],
					"source" : [ "obj-35", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-10", 0 ],
					"source" : [ "obj-36", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-15", 0 ],
					"source" : [ "obj-37", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-36", 0 ],
					"midpoints" : [ 784.5, 229.25, 687.5, 229.25 ],
					"source" : [ "obj-38", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-12", 15 ],
					"source" : [ "obj-39", 15 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-12", 14 ],
					"source" : [ "obj-39", 14 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-12", 13 ],
					"source" : [ "obj-39", 13 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-12", 12 ],
					"source" : [ "obj-39", 12 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-12", 11 ],
					"source" : [ "obj-39", 11 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-12", 10 ],
					"source" : [ "obj-39", 10 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-12", 9 ],
					"source" : [ "obj-39", 9 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-12", 8 ],
					"source" : [ "obj-39", 8 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-12", 7 ],
					"source" : [ "obj-39", 7 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-12", 6 ],
					"source" : [ "obj-39", 6 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-12", 5 ],
					"source" : [ "obj-39", 5 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-12", 4 ],
					"source" : [ "obj-39", 4 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-12", 3 ],
					"source" : [ "obj-39", 3 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-12", 2 ],
					"source" : [ "obj-39", 2 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-12", 1 ],
					"source" : [ "obj-39", 1 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-12", 0 ],
					"source" : [ "obj-39", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-22", 0 ],
					"source" : [ "obj-42", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-11", 0 ],
					"midpoints" : [ 654.5, 405.0, 44.5, 405.0 ],
					"order" : 0,
					"source" : [ "obj-45", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-14", 0 ],
					"midpoints" : [ 654.5, 458.0, 43.25, 458.0 ],
					"order" : 1,
					"source" : [ "obj-45", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-10", 0 ],
					"midpoints" : [ 804.5, 325.0, 654.5, 325.0 ],
					"source" : [ "obj-76", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-33", 0 ],
					"source" : [ "obj-8", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-11", 1 ],
					"source" : [ "obj-9", 0 ]
				}

			}
 ],
		"parameters" : 		{
			"obj-12" : [ "live.gain~[3]", "loudspeakers", 0 ],
			"obj-17::obj-1" : [ "live.menu", "live.menu", 0 ],
			"obj-17::obj-12::obj-4" : [ "live.numbox", "live.numbox", 0 ],
			"obj-17::obj-182" : [ "spat_input_mute_button", "spat_input_mute_button", 0 ],
			"obj-17::obj-2" : [ "live.gain~", " ", 0 ],
			"obj-17::obj-26::obj-56" : [ "live.button[1]", "live.button[1]", 0 ],
			"obj-17::obj-26::obj-58" : [ "live.toggle[1]", "live.toggle[1]", 0 ],
			"obj-17::obj-26::obj-59" : [ "live.numbox[1]", "live.numbox[1]", 0 ],
			"obj-17::obj-43::obj-8" : [ "live.dial", "freq", 0 ],
			"obj-17::obj-46::obj-36" : [ "select folder[1]", "select folder", 0 ],
			"obj-17::obj-46::obj-70" : [ "live.toggle[2]", "live.toggle", 0 ],
			"obj-17::obj-46::obj-8" : [ "live.drop", "live.drop", 0 ],
			"obj-17::obj-5::obj-12" : [ "live.button", "live.button", 0 ],
			"obj-29::obj-11" : [ "live.text[4]", "live.text", 0 ],
			"obj-29::obj-110" : [ "live.text[5]", "live.text", 0 ],
			"obj-29::obj-16" : [ "live.text[1]", "live.text", 0 ],
			"obj-29::obj-55" : [ "live.text[3]", "live.text", 0 ],
			"obj-29::obj-606" : [ "live.text[2]", "live.text", 0 ],
			"obj-29::obj-607" : [ "live.button[2]", "live.button", 0 ],
			"obj-32" : [ "live.tab[1]", "live.tab[1]", 0 ],
			"obj-33::obj-10" : [ "live.numbox[2]", "live.numbox", 0 ],
			"obj-33::obj-15" : [ "live.numbox[5]", "live.numbox", 0 ],
			"obj-33::obj-19" : [ "live.numbox[6]", "live.numbox", 0 ],
			"obj-33::obj-3" : [ "live.tab", "live.tab", 0 ],
			"obj-33::obj-7" : [ "live.numbox[7]", "live.numbox", 0 ],
			"obj-48::obj-11" : [ "live.text[260]", "live.text", 0 ],
			"obj-76::obj-102" : [ "live.toggle[436]", "live.toggle", 0 ],
			"obj-76::obj-3" : [ "live.text[12]", "live.text[9]", 0 ],
			"obj-76::obj-57" : [ "live.text[9]", "live.text[9]", 0 ],
			"obj-76::obj-58" : [ "live.text[10]", "live.text[9]", 0 ],
			"obj-76::obj-62" : [ "live.text[15]", "live.text[9]", 0 ],
			"obj-76::obj-72" : [ "live.text[14]", "live.text[8]", 0 ],
			"obj-9::obj-1" : [ "live.menu[1]", "live.menu", 0 ],
			"obj-9::obj-12::obj-4" : [ "live.numbox[3]", "live.numbox", 0 ],
			"obj-9::obj-182" : [ "spat_input_mute_button[1]", "spat_input_mute_button", 0 ],
			"obj-9::obj-2" : [ "live.gain~[4]", " ", 0 ],
			"obj-9::obj-26::obj-56" : [ "live.button[4]", "live.button[1]", 0 ],
			"obj-9::obj-26::obj-58" : [ "live.toggle[4]", "live.toggle[1]", 0 ],
			"obj-9::obj-26::obj-59" : [ "live.numbox[4]", "live.numbox[1]", 0 ],
			"obj-9::obj-43::obj-8" : [ "live.dial[1]", "freq", 0 ],
			"obj-9::obj-46::obj-36" : [ "select folder[2]", "select folder", 0 ],
			"obj-9::obj-46::obj-70" : [ "live.toggle[3]", "live.toggle", 0 ],
			"obj-9::obj-46::obj-8" : [ "live.drop[1]", "live.drop", 0 ],
			"obj-9::obj-5::obj-12" : [ "live.button[3]", "live.button", 0 ],
			"parameterbanks" : 			{
				"0" : 				{
					"index" : 0,
					"name" : "",
					"parameters" : [ "-", "-", "-", "-", "-", "-", "-", "-" ]
				}

			}
,
			"parameter_overrides" : 			{
				"obj-29::obj-607" : 				{
					"parameter_longname" : "live.button[2]"
				}
,
				"obj-33::obj-15" : 				{
					"parameter_longname" : "live.numbox[5]"
				}
,
				"obj-33::obj-19" : 				{
					"parameter_longname" : "live.numbox[6]"
				}
,
				"obj-33::obj-7" : 				{
					"parameter_longname" : "live.numbox[7]"
				}
,
				"obj-76::obj-3" : 				{
					"parameter_longname" : "live.text[12]"
				}
,
				"obj-76::obj-62" : 				{
					"parameter_longname" : "live.text[15]"
				}
,
				"obj-9::obj-1" : 				{
					"parameter_longname" : "live.menu[1]"
				}
,
				"obj-9::obj-12::obj-4" : 				{
					"parameter_longname" : "live.numbox[3]"
				}
,
				"obj-9::obj-182" : 				{
					"parameter_longname" : "spat_input_mute_button[1]"
				}
,
				"obj-9::obj-2" : 				{
					"parameter_longname" : "live.gain~[4]"
				}
,
				"obj-9::obj-26::obj-56" : 				{
					"parameter_longname" : "live.button[4]"
				}
,
				"obj-9::obj-26::obj-58" : 				{
					"parameter_longname" : "live.toggle[4]"
				}
,
				"obj-9::obj-26::obj-59" : 				{
					"parameter_longname" : "live.numbox[4]"
				}
,
				"obj-9::obj-43::obj-8" : 				{
					"parameter_longname" : "live.dial[1]"
				}
,
				"obj-9::obj-46::obj-36" : 				{
					"parameter_longname" : "select folder[2]"
				}
,
				"obj-9::obj-46::obj-70" : 				{
					"parameter_longname" : "live.toggle[3]"
				}
,
				"obj-9::obj-46::obj-8" : 				{
					"parameter_longname" : "live.drop[1]"
				}
,
				"obj-9::obj-5::obj-12" : 				{
					"parameter_longname" : "live.button[3]"
				}

			}
,
			"inherited_shortname" : 1
		}
,
		"dependency_cache" : [ 			{
				"name" : "ircam-cnrs-spat-2025-alpha.png",
				"bootpath" : "~/Documents/Max 9/Packages/spat5/media/images",
				"patcherrelativepath" : "../../../Max 9/Packages/spat5/media/images",
				"type" : "PNG",
				"implicit" : 1
			}
, 			{
				"name" : "spat5.align~.mxo",
				"type" : "iLaX"
			}
, 			{
				"name" : "spat5.around.maxpat",
				"bootpath" : "~/Documents/Max 9/Packages/spat5/patchers",
				"patcherrelativepath" : "../../../Max 9/Packages/spat5/patchers",
				"type" : "JSON",
				"implicit" : 1
			}
, 			{
				"name" : "spat5.cascade~.mxo",
				"type" : "iLaX"
			}
, 			{
				"name" : "spat5.copyright.maxpat",
				"bootpath" : "~/Documents/Max 9/Packages/spat5/patchers",
				"patcherrelativepath" : "../../../Max 9/Packages/spat5/patchers",
				"type" : "JSON",
				"implicit" : 1
			}
, 			{
				"name" : "spat5.cpu.mxo",
				"type" : "iLaX"
			}
, 			{
				"name" : "spat5.digest.js",
				"bootpath" : "~/Documents/Max 9/Packages/spat5/javascript",
				"patcherrelativepath" : "../../../Max 9/Packages/spat5/javascript",
				"type" : "TEXT",
				"implicit" : 1
			}
, 			{
				"name" : "spat5.equalizer.mxo",
				"type" : "iLaX"
			}
, 			{
				"name" : "spat5.gui.control.maxpat",
				"bootpath" : "~/Documents/Max 9/Packages/spat5/patchers",
				"patcherrelativepath" : "../../../Max 9/Packages/spat5/patchers",
				"type" : "JSON",
				"implicit" : 1
			}
, 			{
				"name" : "spat5.hostinfos.mxo",
				"type" : "iLaX"
			}
, 			{
				"name" : "spat5.input~.maxpat",
				"bootpath" : "~/Documents/Max 9/Packages/spat5/patchers",
				"patcherrelativepath" : "../../../Max 9/Packages/spat5/patchers",
				"type" : "JSON",
				"implicit" : 1
			}
, 			{
				"name" : "spat5.loop.png",
				"bootpath" : "~/Documents/Max 9/Packages/spat5/media/images",
				"patcherrelativepath" : "../../../Max 9/Packages/spat5/media/images",
				"type" : "PNG",
				"implicit" : 1
			}
, 			{
				"name" : "spat5.monitor.maxpat",
				"bootpath" : "~/Documents/Max 9/Packages/spat5/patchers",
				"patcherrelativepath" : "../../../Max 9/Packages/spat5/patchers",
				"type" : "JSON",
				"implicit" : 1
			}
, 			{
				"name" : "spat5.openpatcher.maxpat",
				"bootpath" : "~/Documents/Max 9/Packages/spat5/patchers",
				"patcherrelativepath" : "../../../Max 9/Packages/spat5/patchers",
				"type" : "JSON",
				"implicit" : 1
			}
, 			{
				"name" : "spat5.oper.mxo",
				"type" : "iLaX"
			}
, 			{
				"name" : "spat5.osc.prepend.mxo",
				"type" : "iLaX"
			}
, 			{
				"name" : "spat5.osc.route.mxo",
				"type" : "iLaX"
			}
, 			{
				"name" : "spat5.osc.view.mxo",
				"type" : "iLaX"
			}
, 			{
				"name" : "spat5.rms~.mxo",
				"type" : "iLaX"
			}
, 			{
				"name" : "spat5.spat~.mxo",
				"type" : "iLaX"
			}
, 			{
				"name" : "spat5.style.js",
				"bootpath" : "~/Documents/Max 9/Packages/spat5/javascript",
				"patcherrelativepath" : "../../../Max 9/Packages/spat5/javascript",
				"type" : "TEXT",
				"implicit" : 1
			}
, 			{
				"name" : "thru.maxpat",
				"bootpath" : "C74:/patchers/m4l/Pluggo for Live resources/patches",
				"type" : "JSON",
				"implicit" : 1
			}
 ],
		"autosave" : 0,
		"bgcolor" : [ 0.279471418544607, 0.279471350143365, 0.279471368104493, 1.0 ],
		"editing_bgcolor" : [ 0.279471418544607, 0.279471350143365, 0.279471368104493, 1.0 ],
		"saved_attribute_attributes" : 		{
			"accentcolor" : 			{
				"expression" : "themecolor.theme_accentcolor"
			}
,
			"bubble_bgcolor" : 			{
				"expression" : "themecolor.theme_bubble_bgcolor"
			}
,
			"bubble_outlinecolor" : 			{
				"expression" : "themecolor.theme_bubble_outlinecolor"
			}
,
			"clearcolor" : 			{
				"expression" : "themecolor.theme_clearcolor"
			}
,
			"color" : 			{
				"expression" : "themecolor.theme_color"
			}
,
			"editing_bgcolor" : 			{
				"expression" : "themecolor.live_surface_bg"
			}
,
			"elementcolor" : 			{
				"expression" : "themecolor.theme_elementcolor"
			}
,
			"locked_bgcolor" : 			{
				"expression" : "themecolor.live_surface_bg"
			}
,
			"patchlinecolor" : 			{
				"expression" : "themecolor.theme_patchlinecolor"
			}
,
			"selectioncolor" : 			{
				"expression" : "themecolor.theme_selectioncolor"
			}
,
			"stripecolor" : 			{
				"expression" : "themecolor.theme_stripecolor"
			}
,
			"textcolor" : 			{
				"expression" : "themecolor.live_control_fg"
			}

		}

	}

}
