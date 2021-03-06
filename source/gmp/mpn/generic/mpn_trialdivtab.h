#if GMP_LIMB_BITS != 32
#error This table is for GMP_LIMB_BITS = 32
#endif

#if GMP_NAIL_BITS != 0
#error This table does not support nails
#endif

#ifdef WANT_dtab
  P(3,CNST_LIMB(0xaaaaaaab),CNST_LIMB(0x55555555)),
  P(5,CNST_LIMB(0xcccccccd),CNST_LIMB(0x33333333)),
  P(7,CNST_LIMB(0xb6db6db7),CNST_LIMB(0x24924924)),
  P(11,CNST_LIMB(0xba2e8ba3),CNST_LIMB(0x1745d174)),
  P(13,CNST_LIMB(0xc4ec4ec5),CNST_LIMB(0x13b13b13)),
  P(17,CNST_LIMB(0xf0f0f0f1),CNST_LIMB(0xf0f0f0f)),
  P(19,CNST_LIMB(0x286bca1b),CNST_LIMB(0xd79435e)),
  P(23,CNST_LIMB(0xe9bd37a7),CNST_LIMB(0xb21642c)),
  P(29,CNST_LIMB(0x4f72c235),CNST_LIMB(0x8d3dcb0)),
  P(31,CNST_LIMB(0xbdef7bdf),CNST_LIMB(0x8421084)),
  P(37,CNST_LIMB(0x914c1bad),CNST_LIMB(0x6eb3e45)),
  P(41,CNST_LIMB(0xc18f9c19),CNST_LIMB(0x63e7063)),
  P(43,CNST_LIMB(0x2fa0be83),CNST_LIMB(0x5f417d0)),
  P(47,CNST_LIMB(0x677d46cf),CNST_LIMB(0x572620a)),
  P(53,CNST_LIMB(0x8c13521d),CNST_LIMB(0x4d4873e)),
  P(59,CNST_LIMB(0xa08ad8f3),CNST_LIMB(0x456c797)),
  P(61,CNST_LIMB(0xc10c9715),CNST_LIMB(0x4325c53)),
  P(67,CNST_LIMB(0x7a44c6b),CNST_LIMB(0x3d22635)),
  P(71,CNST_LIMB(0xe327a977),CNST_LIMB(0x39b0ad1)),
  P(73,CNST_LIMB(0xc7e3f1f9),CNST_LIMB(0x381c0e0)),
  P(79,CNST_LIMB(0x613716af),CNST_LIMB(0x33d91d2)),
  P(83,CNST_LIMB(0x2b2e43db),CNST_LIMB(0x3159721)),
  P(89,CNST_LIMB(0xfa3f47e9),CNST_LIMB(0x2e05c0b)),
  P(97,CNST_LIMB(0x5f02a3a1),CNST_LIMB(0x2a3a0fd)),
  P(101,CNST_LIMB(0x7c32b16d),CNST_LIMB(0x288df0c)),
  P(103,CNST_LIMB(0xd3431b57),CNST_LIMB(0x27c4597)),
  P(107,CNST_LIMB(0x8d28ac43),CNST_LIMB(0x2647c69)),
  P(109,CNST_LIMB(0xda6c0965),CNST_LIMB(0x2593f69)),
  P(113,CNST_LIMB(0xfdbc091),CNST_LIMB(0x243f6f0)),
  P(127,CNST_LIMB(0xefdfbf7f),CNST_LIMB(0x2040810)),
  P(131,CNST_LIMB(0xc9484e2b),CNST_LIMB(0x1f44659)),
  P(137,CNST_LIMB(0x77975b9),CNST_LIMB(0x1de5d6e)),
  P(139,CNST_LIMB(0x70586723),CNST_LIMB(0x1d77b65)),
  P(149,CNST_LIMB(0x8ce2cabd),CNST_LIMB(0x1b7d6c3)),
  P(151,CNST_LIMB(0xbf937f27),CNST_LIMB(0x1b20364)),
  P(157,CNST_LIMB(0x2c0685b5),CNST_LIMB(0x1a16d3f)),
  P(163,CNST_LIMB(0x451ab30b),CNST_LIMB(0x1920fb4)),
  P(167,CNST_LIMB(0xdb35a717),CNST_LIMB(0x1886e5f)),
  P(173,CNST_LIMB(0xd516325),CNST_LIMB(0x17ad220)),
  P(179,CNST_LIMB(0xd962ae7b),CNST_LIMB(0x16e1f76)),
  P(181,CNST_LIMB(0x10f8ed9d),CNST_LIMB(0x16a13cd)),
  P(191,CNST_LIMB(0xee936f3f),CNST_LIMB(0x1571ed3)),
  P(193,CNST_LIMB(0x90948f41),CNST_LIMB(0x1539094)),
  P(197,CNST_LIMB(0x3d137e0d),CNST_LIMB(0x14cab88)),
  P(199,CNST_LIMB(0xef46c0f7),CNST_LIMB(0x149539e)),
  P(211,CNST_LIMB(0x6e68575b),CNST_LIMB(0x13698df)),
  P(223,CNST_LIMB(0xdb43bb1f),CNST_LIMB(0x125e227)),
  P(227,CNST_LIMB(0x9ba144cb),CNST_LIMB(0x120b470)),
  P(229,CNST_LIMB(0x478bbced),CNST_LIMB(0x11e2ef3)),
  P(233,CNST_LIMB(0x1fdcd759),CNST_LIMB(0x1194538)),
  P(239,CNST_LIMB(0x437b2e0f),CNST_LIMB(0x112358e)),
  P(241,CNST_LIMB(0x10fef011),CNST_LIMB(0x10fef01)),
  P(251,CNST_LIMB(0x9a020a33),CNST_LIMB(0x105197f)),
  P(257,CNST_LIMB(0xff00ff01),CNST_LIMB(0xff00ff)),
  P(263,CNST_LIMB(0x70e99cb7),CNST_LIMB(0xf92fb2)),
  P(269,CNST_LIMB(0x6205b5c5),CNST_LIMB(0xf3a0d5)),
  P(271,CNST_LIMB(0xa27acdef),CNST_LIMB(0xf1d48b)),
  P(277,CNST_LIMB(0x25e4463d),CNST_LIMB(0xec9791)),
  P(281,CNST_LIMB(0x749cb29),CNST_LIMB(0xe93965)),
  P(283,CNST_LIMB(0xc9b97113),CNST_LIMB(0xe79372)),
  P(293,CNST_LIMB(0x84ce32ad),CNST_LIMB(0xdfac1f)),
  P(307,CNST_LIMB(0xc74be1fb),CNST_LIMB(0xd578e9)),
  P(311,CNST_LIMB(0xa7198487),CNST_LIMB(0xd2ba08)),
  P(313,CNST_LIMB(0x39409d09),CNST_LIMB(0xd16154)),
  P(317,CNST_LIMB(0x6f71de15),CNST_LIMB(0xcebcf8)),
  P(331,CNST_LIMB(0xbfce8063),CNST_LIMB(0xc5fe74)),
  P(337,CNST_LIMB(0xf61fe7b1),CNST_LIMB(0xc27806)),
  P(347,CNST_LIMB(0x70e046d3),CNST_LIMB(0xbcdd53)),
  P(349,CNST_LIMB(0xf1545af5),CNST_LIMB(0xbbc840)),
  P(353,CNST_LIMB(0x9a7862a1),CNST_LIMB(0xb9a786)),
  P(359,CNST_LIMB(0x2a128a57),CNST_LIMB(0xb68d31)),
  P(367,CNST_LIMB(0xb7747d8f),CNST_LIMB(0xb2927c)),
  P(373,CNST_LIMB(0xbb5e06dd),CNST_LIMB(0xafb321)),
  P(379,CNST_LIMB(0x12e9b5b3),CNST_LIMB(0xaceb0f)),
  P(383,CNST_LIMB(0xec9dbe7f),CNST_LIMB(0xab1cbd)),
  P(389,CNST_LIMB(0xec41cf4d),CNST_LIMB(0xa87917)),
  P(397,CNST_LIMB(0xaec02945),CNST_LIMB(0xa513fd)),
  P(401,CNST_LIMB(0x8382df71),CNST_LIMB(0xa36e71)),
  P(409,CNST_LIMB(0x84b1c2a9),CNST_LIMB(0xa03c16)),
  P(419,CNST_LIMB(0x75eb3a0b),CNST_LIMB(0x9c6916)),
  P(421,CNST_LIMB(0xfa86fe2d),CNST_LIMB(0x9baade)),
  P(431,CNST_LIMB(0x3f8df54f),CNST_LIMB(0x980e41)),
  P(433,CNST_LIMB(0x975a751),CNST_LIMB(0x975a75)),
  P(439,CNST_LIMB(0xc3efac07),CNST_LIMB(0x9548e4)),
  P(443,CNST_LIMB(0xa8299b73),CNST_LIMB(0x93efd1)),
  P(449,CNST_LIMB(0x9ba70e41),CNST_LIMB(0x91f5bc)),
  P(457,CNST_LIMB(0x23d9e879),CNST_LIMB(0x8f67a1)),
  P(461,CNST_LIMB(0xc494d305),CNST_LIMB(0x8e2917)),
  P(463,CNST_LIMB(0xab67652f),CNST_LIMB(0x8d8be3)),
  P(467,CNST_LIMB(0xfb10fe5b),CNST_LIMB(0x8c5584)),
  P(479,CNST_LIMB(0xbf54fa1f),CNST_LIMB(0x88d180)),
  P(487,CNST_LIMB(0xb98f81d7),CNST_LIMB(0x869222)),
  P(491,CNST_LIMB(0xe90f1ec3),CNST_LIMB(0x85797b)),
  P(499,CNST_LIMB(0xbed87f3b),CNST_LIMB(0x8355ac)),
  P(503,CNST_LIMB(0x16e70fc7),CNST_LIMB(0x824a4e)),
  P(509,CNST_LIMB(0x9dece355),CNST_LIMB(0x80c121)),
  P(521,CNST_LIMB(0x73f62c39),CNST_LIMB(0x7dc9f3)),
  P(523,CNST_LIMB(0xad46f9a3),CNST_LIMB(0x7d4ece)),
  P(541,CNST_LIMB(0x24e8d035),CNST_LIMB(0x79237d)),
  P(547,CNST_LIMB(0x2319bd8b),CNST_LIMB(0x77cf53)),
  P(557,CNST_LIMB(0xc7ed9da5),CNST_LIMB(0x75a8ac)),
  P(563,CNST_LIMB(0xfea2c8fb),CNST_LIMB(0x7467ac)),
  P(569,CNST_LIMB(0xce0f4c09),CNST_LIMB(0x732d70)),
  P(571,CNST_LIMB(0x544986f3),CNST_LIMB(0x72c62a)),
  P(577,CNST_LIMB(0x55a10dc1),CNST_LIMB(0x7194a1)),
  P(587,CNST_LIMB(0x85e33763),CNST_LIMB(0x6fa549)),
  P(593,CNST_LIMB(0xd84886b1),CNST_LIMB(0x6e8419)),
  P(599,CNST_LIMB(0x31260967),CNST_LIMB(0x6d68b5)),
  P(601,CNST_LIMB(0xd1ff25e9),CNST_LIMB(0x6d0b80)),
  P(607,CNST_LIMB(0x5b84d99f),CNST_LIMB(0x6bf790)),
  P(613,CNST_LIMB(0x1335df6d),CNST_LIMB(0x6ae907)),
  P(617,CNST_LIMB(0x75d5add9),CNST_LIMB(0x6a3799)),
  P(619,CNST_LIMB(0x3c619a43),CNST_LIMB(0x69dfbd)),
  P(631,CNST_LIMB(0x4767747),CNST_LIMB(0x67dc4c)),
  P(641,CNST_LIMB(0x663d81),CNST_LIMB(0x663d80)),
  P(643,CNST_LIMB(0x671ddc2b),CNST_LIMB(0x65ec17)),
  P(647,CNST_LIMB(0xc1e12337),CNST_LIMB(0x654ac8)),
  P(653,CNST_LIMB(0x9cd09045),CNST_LIMB(0x645c85)),
  P(659,CNST_LIMB(0x91496b9b),CNST_LIMB(0x637299)),
  P(661,CNST_LIMB(0xc7d7b8bd),CNST_LIMB(0x632591)),
  P(673,CNST_LIMB(0x9f006161),CNST_LIMB(0x6160ff)),
  P(677,CNST_LIMB(0x5e28152d),CNST_LIMB(0x60cdb5)),
  P(683,CNST_LIMB(0xbfe803),CNST_LIMB(0x5ff401)),
  P(691,CNST_LIMB(0x9e907c7b),CNST_LIMB(0x5ed79e)),
  P(701,CNST_LIMB(0x76528895),CNST_LIMB(0x5d7d42)),
  P(709,CNST_LIMB(0x1ce2c0d),CNST_LIMB(0x5c6f35)),
  P(719,CNST_LIMB(0xbed7c42f),CNST_LIMB(0x5b2618)),
  P(727,CNST_LIMB(0xd4b010e7),CNST_LIMB(0x5a2553)),
  P(733,CNST_LIMB(0x1ebbe575),CNST_LIMB(0x59686c)),
  P(739,CNST_LIMB(0xb47b52cb),CNST_LIMB(0x58ae97)),
  P(743,CNST_LIMB(0x64f3f0d7),CNST_LIMB(0x58345f)),
  P(751,CNST_LIMB(0x316d6c0f),CNST_LIMB(0x5743d5)),
  P(757,CNST_LIMB(0x91c1195d),CNST_LIMB(0x5692c4)),
  P(761,CNST_LIMB(0xa27b1f49),CNST_LIMB(0x561e46)),
  P(769,CNST_LIMB(0xe508fd01),CNST_LIMB(0x5538ed)),
  P(773,CNST_LIMB(0x133551cd),CNST_LIMB(0x54c807)),
  P(787,CNST_LIMB(0x2d8a3f1b),CNST_LIMB(0x5345ef)),
  P(797,CNST_LIMB(0xc34ad735),CNST_LIMB(0x523a75)),
  P(809,CNST_LIMB(0xa714919),CNST_LIMB(0x510237)),
  P(811,CNST_LIMB(0x24eea383),CNST_LIMB(0x50cf12)),
  P(821,CNST_LIMB(0x42ba771d),CNST_LIMB(0x4fd319)),
  P(823,CNST_LIMB(0x7772287),CNST_LIMB(0x4fa170)),
  P(827,CNST_LIMB(0x5e69ddf3),CNST_LIMB(0x4f3ed6)),
  P(829,CNST_LIMB(0x3b4a6c15),CNST_LIMB(0x4f0de5)),
  P(839,CNST_LIMB(0xc606b677),CNST_LIMB(0x4e1cae)),
  P(853,CNST_LIMB(0x46d3e1fd),CNST_LIMB(0x4cd47b)),
  P(857,CNST_LIMB(0x484a14e9),CNST_LIMB(0x4c78ae)),
  P(859,CNST_LIMB(0x1ce874d3),CNST_LIMB(0x4c4b19)),
  P(863,CNST_LIMB(0x473189f),CNST_LIMB(0x4bf093)),
  P(877,CNST_LIMB(0x372b7e65),CNST_LIMB(0x4aba3c)),
  P(881,CNST_LIMB(0x4f9e5d91),CNST_LIMB(0x4a6360)),
  P(883,CNST_LIMB(0x446bd9bb),CNST_LIMB(0x4a383e)),
  P(887,CNST_LIMB(0xe777c647),CNST_LIMB(0x49e28f)),
  P(907,CNST_LIMB(0xf61f0c23),CNST_LIMB(0x48417b)),
  P(911,CNST_LIMB(0xa5cbbb6f),CNST_LIMB(0x47f043)),
  P(919,CNST_LIMB(0x69daac27),CNST_LIMB(0x474ff2)),
  P(929,CNST_LIMB(0x637aa061),CNST_LIMB(0x468b6f)),
  P(937,CNST_LIMB(0x1fb15099),CNST_LIMB(0x45f13f)),
  P(941,CNST_LIMB(0x712c5825),CNST_LIMB(0x45a522)),
  P(947,CNST_LIMB(0xff30637b),CNST_LIMB(0x45342c)),
  P(953,CNST_LIMB(0x1131289),CNST_LIMB(0x44c4a2)),
  P(967,CNST_LIMB(0xf5acdf7),CNST_LIMB(0x43c5c2)),
  P(971,CNST_LIMB(0x4d3f89e3),CNST_LIMB(0x437e49)),
  P(977,CNST_LIMB(0xd2253531),CNST_LIMB(0x43142d)),
  P(983,CNST_LIMB(0x7bf69fe7),CNST_LIMB(0x42ab5c)),
  P(991,CNST_LIMB(0xcfb1781f),CNST_LIMB(0x422195)),
#define SMALLEST_OMITTED_PRIME 997
#endif
#ifdef WANT_ptab
  {CNST_LIMB(0x6a61043),{CNST_LIMB(0x3407e2f4),5,CNST_LIMB(0x359960e),CNST_LIMB(0x280d2ab),CNST_LIMB(0x356bfe7),CNST_LIMB(0x26f3e6),CNST_LIMB(0x3219349)},0,8},
  {CNST_LIMB(0x37ed0ed),{CNST_LIMB(0x24f56131),6,CNST_LIMB(0xd66c6b),CNST_LIMB(0x25cccb7),CNST_LIMB(0xd960c3),CNST_LIMB(0x1cfe319),CNST_LIMB(0x101d79a)},8,5},
  {CNST_LIMB(0x23cd611f),{CNST_LIMB(0xc99fec6b),2,CNST_LIMB(0x5625827),CNST_LIMB(0x5adef0d),CNST_LIMB(0x1642bcf1),CNST_LIMB(0x1949f611),CNST_LIMB(0x1e01afdb)},13,5},
  {CNST_LIMB(0x20691a3),{CNST_LIMB(0xf983aa48),6,CNST_LIMB(0xc451c6),CNST_LIMB(0x1f30a00),CNST_LIMB(0x1882017),CNST_LIMB(0x13584ab),CNST_LIMB(0x1dc4b51)},18,4},
  {CNST_LIMB(0x55a60cb),{CNST_LIMB(0x7e961d36),5,CNST_LIMB(0x4683abb),CNST_LIMB(0xb480fe),CNST_LIMB(0x11ac11e),CNST_LIMB(0x4e42709),CNST_LIMB(0x485b829)},22,4},
  {CNST_LIMB(0x9f9f361),{CNST_LIMB(0x9a91f75d),4,CNST_LIMB(0x6973b87),CNST_LIMB(0x902120d),CNST_LIMB(0x1b39c8b),CNST_LIMB(0x2243a6d),CNST_LIMB(0x39cc32a)},26,4},
  {CNST_LIMB(0x1627b25d),{CNST_LIMB(0x71c1e6d9),3,CNST_LIMB(0xc4b5601),CNST_LIMB(0x572f241),CNST_LIMB(0x123561d3),CNST_LIMB(0xacd1a4e),CNST_LIMB(0xe50caef)},30,4},
  {CNST_LIMB(0x2676ed77),{CNST_LIMB(0xa9f355bd),2,CNST_LIMB(0x19366f36),CNST_LIMB(0x262fe82f),CNST_LIMB(0x19f58916),CNST_LIMB(0x1d3362e9),CNST_LIMB(0x1ce7cbf5)},34,4},
  {CNST_LIMB(0x3fcf739d),{CNST_LIMB(0xc2c54b),2,CNST_LIMB(0xc2318c),CNST_LIMB(0x351d4004),CNST_LIMB(0x1fd221a2),CNST_LIMB(0x9cd3902),CNST_LIMB(0x18b387c)},38,4},
  {CNST_LIMB(0x5f281a99),{CNST_LIMB(0x585bc466),1,CNST_LIMB(0x41afcace),CNST_LIMB(0x4b626b7b),CNST_LIMB(0x1a993cb2),CNST_LIMB(0x348290b9),CNST_LIMB(0x148c969a)},42,4},
  {CNST_LIMB(0xb0e211),{CNST_LIMB(0x72813080),8,CNST_LIMB(0x59436e),CNST_LIMB(0x1b120),CNST_LIMB(0x2131fd),CNST_LIMB(0x65359c),CNST_LIMB(0x6c36d8)},46,3},
  {CNST_LIMB(0xccc817),{CNST_LIMB(0x40075c3b),8,CNST_LIMB(0x5e340),CNST_LIMB(0xa0435d),CNST_LIMB(0xb7b3f4),CNST_LIMB(0xbc8eaa),CNST_LIMB(0x7f505d)},49,3},
  {CNST_LIMB(0x102dedd),{CNST_LIMB(0xfa529227),7,CNST_LIMB(0x29bf97),CNST_LIMB(0xd2b1f),CNST_LIMB(0x48ce87),CNST_LIMB(0x27dbb5),CNST_LIMB(0xbc2d73)},52,3},
  {CNST_LIMB(0x1341eff),{CNST_LIMB(0xa96426ad),7,CNST_LIMB(0xd654d4),CNST_LIMB(0x6292bc),CNST_LIMB(0x21e29),CNST_LIMB(0x8ee815),CNST_LIMB(0x4b678e)},55,3},
  {CNST_LIMB(0x163888f),{CNST_LIMB(0x70a9b660),7,CNST_LIMB(0x75d938),CNST_LIMB(0xaf0b1d),CNST_LIMB(0x30460d),CNST_LIMB(0x732299),CNST_LIMB(0xce6686)},58,3},
  {CNST_LIMB(0x1c7ff8d),{CNST_LIMB(0x1f709059),7,CNST_LIMB(0x148403d),CNST_LIMB(0x9c1ebe),CNST_LIMB(0xeee5da),CNST_LIMB(0x3bed2f),CNST_LIMB(0x1bc276d)},61,3},
  {CNST_LIMB(0x21b8e8f),{CNST_LIMB(0xe5d9bd6c),6,CNST_LIMB(0xf99e69),CNST_LIMB(0x13de9a),CNST_LIMB(0x13ae4f9),CNST_LIMB(0x90e465),CNST_LIMB(0x75aa6a)},64,3},
  {CNST_LIMB(0x28c4daf),{CNST_LIMB(0x91dfd2d4),6,CNST_LIMB(0x131a7a4),CNST_LIMB(0xced3f9),CNST_LIMB(0x5fc1d1),CNST_LIMB(0x1a63184),CNST_LIMB(0xd36406)},67,3},
  {CNST_LIMB(0x2ede03d),{CNST_LIMB(0x5d954a31),6,CNST_LIMB(0x128cb45),CNST_LIMB(0x21aecb),CNST_LIMB(0x1981fad),CNST_LIMB(0x6e6aac),CNST_LIMB(0x1a5536c)},70,3},
  {CNST_LIMB(0x35d9a99),{CNST_LIMB(0x30404d26),6,CNST_LIMB(0x361a94),CNST_LIMB(0x2ab8034),CNST_LIMB(0x196715e),CNST_LIMB(0xe04b2b),CNST_LIMB(0x2bf7b04)},73,3},
  {CNST_LIMB(0x3e18615),{CNST_LIMB(0x7da4f6c),6,CNST_LIMB(0x3bcf4ab),CNST_LIMB(0x1432229),CNST_LIMB(0x2dc22df),CNST_LIMB(0x1253154),CNST_LIMB(0x7da79b)},76,3},
  {CNST_LIMB(0x4881841),{CNST_LIMB(0xc3ef7d16),5,CNST_LIMB(0x23ab1c8),CNST_LIMB(0x23d33fb),CNST_LIMB(0x277d7e7),CNST_LIMB(0x749798),CNST_LIMB(0x3faa198)},79,3},
  {CNST_LIMB(0x504eb9d),{CNST_LIMB(0x98081137),5,CNST_LIMB(0x50fb9),CNST_LIMB(0x31734bf),CNST_LIMB(0x2d9f6b8),CNST_LIMB(0x3b1b0a3),CNST_LIMB(0x4b3b8d4)},82,3},
  {CNST_LIMB(0x5a363b5),{CNST_LIMB(0x6b3be150),5,CNST_LIMB(0x247792f),CNST_LIMB(0x20e22e1),CNST_LIMB(0x454996c),CNST_LIMB(0x3f72ee2),CNST_LIMB(0x16067a8)},85,3},
  {CNST_LIMB(0x62c59c3),{CNST_LIMB(0x4bc114ed),5,CNST_LIMB(0x2e59fc5),CNST_LIMB(0x3008b15),CNST_LIMB(0x5162c12),CNST_LIMB(0x38af0a6),CNST_LIMB(0x364f36e)},88,3},
  {CNST_LIMB(0x71cab57),{CNST_LIMB(0x1ff6e506),5,CNST_LIMB(0x714931b),CNST_LIMB(0x3f91ab6),CNST_LIMB(0x22aa414),CNST_LIMB(0x146a171),CNST_LIMB(0x709d520)},91,3},
  {CNST_LIMB(0x7f35ef3),{CNST_LIMB(0x196a38f),5,CNST_LIMB(0x19421a0),CNST_LIMB(0x7b1b930),CNST_LIMB(0x35f1501),CNST_LIMB(0x5d2c30b),CNST_LIMB(0x17120c5)},94,3},
  {CNST_LIMB(0x939999d),{CNST_LIMB(0xbc02c5c7),4,CNST_LIMB(0x6eccc71),CNST_LIMB(0xef9279),CNST_LIMB(0x413d0c3),CNST_LIMB(0xc99b8c),CNST_LIMB(0x4fea894)},97,3},
  {CNST_LIMB(0xaa2acff),{CNST_LIMB(0x81208448),4,CNST_LIMB(0xbfc818),CNST_LIMB(0x2d5bd83),CNST_LIMB(0x3d8740b),CNST_LIMB(0x93899fb),CNST_LIMB(0x25ffe98)},100,3},
  {CNST_LIMB(0xb870189),{CNST_LIMB(0x63540cb5),4,CNST_LIMB(0x265de3a),CNST_LIMB(0x27cce3b),CNST_LIMB(0x76fde07),CNST_LIMB(0x447bb87),CNST_LIMB(0x3206a2e)},103,3},
  {CNST_LIMB(0xcb96fef),{CNST_LIMB(0x41e6f245),4,CNST_LIMB(0x1834154),CNST_LIMB(0x1e2e9d8),CNST_LIMB(0x35efcdf),CNST_LIMB(0x3bf7538),CNST_LIMB(0x7a94328)},106,3},
  {CNST_LIMB(0xdaf1d73),{CNST_LIMB(0x2b53a52a),4,CNST_LIMB(0x9afedea),CNST_LIMB(0x46f3fb),CNST_LIMB(0x8e3c610),CNST_LIMB(0xced433a),CNST_LIMB(0x92db975)},109,3},
  {CNST_LIMB(0xeec4e3d),{CNST_LIMB(0x127970b1),4,CNST_LIMB(0x24ecdf3),CNST_LIMB(0x1810b48),CNST_LIMB(0x49df38a),CNST_LIMB(0xd5b6aa3),CNST_LIMB(0xdad9873)},112,3},
  {CNST_LIMB(0x10313a91),{CNST_LIMB(0xf9eb6341),3,CNST_LIMB(0xd1d9181),CNST_LIMB(0xcd11212),CNST_LIMB(0xf6be0a7),CNST_LIMB(0xbf8f806),CNST_LIMB(0x10178f82)},115,3},
  {CNST_LIMB(0x11793cef),{CNST_LIMB(0xd4d268ca),3,CNST_LIMB(0xb5eaaee),CNST_LIMB(0x35f2db6),CNST_LIMB(0x76a2eec),CNST_LIMB(0x8d5e9c7),CNST_LIMB(0xd05406b)},118,3},
  {CNST_LIMB(0x130b5e75),{CNST_LIMB(0xae270832),3,CNST_LIMB(0x86c340f),CNST_LIMB(0x4fbcabb),CNST_LIMB(0xc5f1cb2),CNST_LIMB(0x52847a),CNST_LIMB(0x1262c44f)},121,3},
  {CNST_LIMB(0x154cb85f),{CNST_LIMB(0x809b4803),3,CNST_LIMB(0x675b8c),CNST_LIMB(0x9e159c),CNST_LIMB(0x91d79ec),CNST_LIMB(0x12b718f9),CNST_LIMB(0x14df0cea)},124,3},
  {CNST_LIMB(0x17790271),{CNST_LIMB(0x5d0053ab),3,CNST_LIMB(0x1545e796),CNST_LIMB(0x49ad4d5),CNST_LIMB(0x6cc0e13),CNST_LIMB(0x14f6fefc),CNST_LIMB(0x75bdf93)},127,3},
  {CNST_LIMB(0x192d52bd),{CNST_LIMB(0x4560327b),3,CNST_LIMB(0x43ac49e),CNST_LIMB(0x1272b91a),CNST_LIMB(0x6ea322),CNST_LIMB(0x6662f7b),CNST_LIMB(0x24444a0)},130,3},
  {CNST_LIMB(0x1af690dd),{CNST_LIMB(0x2fd27496),3,CNST_LIMB(0xd54e83b),CNST_LIMB(0x5f6ffbf),CNST_LIMB(0x894a706),CNST_LIMB(0x4787264),CNST_LIMB(0x632d5f1)},133,3},
  {CNST_LIMB(0x1e3edd3f),{CNST_LIMB(0xed98211),3,CNST_LIMB(0xe091608),CNST_LIMB(0x1158344d),CNST_LIMB(0x849e6ec),CNST_LIMB(0x1e3d6afd),CNST_LIMB(0xd2b549e)},136,3},
  {CNST_LIMB(0x20a97ea1),{CNST_LIMB(0xf59f0efa),2,CNST_LIMB(0x1b5d8999),CNST_LIMB(0x83da735),CNST_LIMB(0x289697c),CNST_LIMB(0x18842148),CNST_LIMB(0x971b719)},139,3},
  {CNST_LIMB(0x2248eb29),{CNST_LIMB(0xdde0fe12),2,CNST_LIMB(0x100191e1),CNST_LIMB(0xe214e26),CNST_LIMB(0xe25d5b),CNST_LIMB(0x15448475),CNST_LIMB(0x18e0bf43)},142,3},
  {CNST_LIMB(0x256db61f),{CNST_LIMB(0xb5bd9743),2,CNST_LIMB(0x1f6dbb46),CNST_LIMB(0x79f112f),CNST_LIMB(0x180b837),CNST_LIMB(0x1fabd504),CNST_LIMB(0xcd4316b)},145,3},
  {CNST_LIMB(0x27be57c3),{CNST_LIMB(0x9c3e44a9),2,CNST_LIMB(0x1189f16e),CNST_LIMB(0x3fe09cb),CNST_LIMB(0x200576bc),CNST_LIMB(0xee0400),CNST_LIMB(0x94268c7)},148,3},
  {CNST_LIMB(0x2a578f87),{CNST_LIMB(0x82f1b049),2,CNST_LIMB(0x1f2a2d6),CNST_LIMB(0xeb97a7d),CNST_LIMB(0x3cbd8b2),CNST_LIMB(0x147ae1f2),CNST_LIMB(0x21252a67)},151,3},
  {CNST_LIMB(0x2e5bc8f9),{CNST_LIMB(0x616b55ac),2,CNST_LIMB(0x18351323),CNST_LIMB(0x1e1d2ed0),CNST_LIMB(0xd05ce1b),CNST_LIMB(0xb659390),CNST_LIMB(0x181b4ed6)},154,3},
  {CNST_LIMB(0x31c4e00f),{CNST_LIMB(0x49335bb4),2,CNST_LIMB(0x7279fb5),CNST_LIMB(0xc36c1b2),CNST_LIMB(0x22bcdb49),CNST_LIMB(0x1b0c3f08),CNST_LIMB(0x3ba3ff9)},157,3},
  {CNST_LIMB(0x3555f625),{CNST_LIMB(0x332f94f8),2,CNST_LIMB(0x2aa8276c),CNST_LIMB(0x152eaa7b),CNST_LIMB(0x114a5023),CNST_LIMB(0x247d32c3),CNST_LIMB(0x29d13845)},160,3},
  {CNST_LIMB(0x38ba8399),{CNST_LIMB(0x20d05c1a),2,CNST_LIMB(0x1d15f19c),CNST_LIMB(0x345992a6),CNST_LIMB(0xd3afbd2),CNST_LIMB(0x2977445b),CNST_LIMB(0x17db69bc)},163,3}
#endif
