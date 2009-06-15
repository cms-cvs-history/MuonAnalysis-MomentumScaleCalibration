import FWCore.ParameterSet.Config as cms

source = cms.Source("PoolSource",
                    fileNames = cms.untracked.vstring(
    "rfio:/castor/cern.ch/user/d/demattia/MuScleFit/Summer08/Zold/Filter_Z_1.root",
    "rfio:/castor/cern.ch/user/d/demattia/MuScleFit/Summer08/Zold/Filter_Z_11.root",
    "rfio:/castor/cern.ch/user/d/demattia/MuScleFit/Summer08/Zold/Filter_Z_12.root",
    "rfio:/castor/cern.ch/user/d/demattia/MuScleFit/Summer08/Zold/Filter_Z_13.root",
    "rfio:/castor/cern.ch/user/d/demattia/MuScleFit/Summer08/Zold/Filter_Z_14.root",
    "rfio:/castor/cern.ch/user/d/demattia/MuScleFit/Summer08/Zold/Filter_Z_15.root",
    "rfio:/castor/cern.ch/user/d/demattia/MuScleFit/Summer08/Zold/Filter_Z_16.root",
    "rfio:/castor/cern.ch/user/d/demattia/MuScleFit/Summer08/Zold/Filter_Z_17.root",
    "rfio:/castor/cern.ch/user/d/demattia/MuScleFit/Summer08/Zold/Filter_Z_18.root",
    "rfio:/castor/cern.ch/user/d/demattia/MuScleFit/Summer08/Zold/Filter_Z_19.root",
    "rfio:/castor/cern.ch/user/d/demattia/MuScleFit/Summer08/Zold/Filter_Z_2.root",
    "rfio:/castor/cern.ch/user/d/demattia/MuScleFit/Summer08/Zold/Filter_Z_20.root",
    "rfio:/castor/cern.ch/user/d/demattia/MuScleFit/Summer08/Zold/Filter_Z_21.root",
    "rfio:/castor/cern.ch/user/d/demattia/MuScleFit/Summer08/Zold/Filter_Z_22.root",
    "rfio:/castor/cern.ch/user/d/demattia/MuScleFit/Summer08/Zold/Filter_Z_23.root",
    "rfio:/castor/cern.ch/user/d/demattia/MuScleFit/Summer08/Zold/Filter_Z_24.root",
    "rfio:/castor/cern.ch/user/d/demattia/MuScleFit/Summer08/Zold/Filter_Z_25.root",
    "rfio:/castor/cern.ch/user/d/demattia/MuScleFit/Summer08/Zold/Filter_Z_26.root",
    "rfio:/castor/cern.ch/user/d/demattia/MuScleFit/Summer08/Zold/Filter_Z_27.root",
    "rfio:/castor/cern.ch/user/d/demattia/MuScleFit/Summer08/Zold/Filter_Z_28.root",
    "rfio:/castor/cern.ch/user/d/demattia/MuScleFit/Summer08/Zold/Filter_Z_29.root",
    "rfio:/castor/cern.ch/user/d/demattia/MuScleFit/Summer08/Zold/Filter_Z_3.root",
    "rfio:/castor/cern.ch/user/d/demattia/MuScleFit/Summer08/Zold/Filter_Z_30.root",
    "rfio:/castor/cern.ch/user/d/demattia/MuScleFit/Summer08/Zold/Filter_Z_31.root",
#    "rfio:/castor/cern.ch/user/d/demattia/MuScleFit/Summer08/Zold/Filter_Z_32.root",
    "rfio:/castor/cern.ch/user/d/demattia/MuScleFit/Summer08/Zold/Filter_Z_33.root",
    "rfio:/castor/cern.ch/user/d/demattia/MuScleFit/Summer08/Zold/Filter_Z_35.root",
    "rfio:/castor/cern.ch/user/d/demattia/MuScleFit/Summer08/Zold/Filter_Z_36.root",
    "rfio:/castor/cern.ch/user/d/demattia/MuScleFit/Summer08/Zold/Filter_Z_37.root",
    "rfio:/castor/cern.ch/user/d/demattia/MuScleFit/Summer08/Zold/Filter_Z_38.root",
    "rfio:/castor/cern.ch/user/d/demattia/MuScleFit/Summer08/Zold/Filter_Z_39.root",
    "rfio:/castor/cern.ch/user/d/demattia/MuScleFit/Summer08/Zold/Filter_Z_4.root",
    "rfio:/castor/cern.ch/user/d/demattia/MuScleFit/Summer08/Zold/Filter_Z_40.root",
    "rfio:/castor/cern.ch/user/d/demattia/MuScleFit/Summer08/Zold/Filter_Z_41.root",
    "rfio:/castor/cern.ch/user/d/demattia/MuScleFit/Summer08/Zold/Filter_Z_42.root",
    "rfio:/castor/cern.ch/user/d/demattia/MuScleFit/Summer08/Zold/Filter_Z_43.root",
    "rfio:/castor/cern.ch/user/d/demattia/MuScleFit/Summer08/Zold/Filter_Z_44.root",
    "rfio:/castor/cern.ch/user/d/demattia/MuScleFit/Summer08/Zold/Filter_Z_45.root",
    "rfio:/castor/cern.ch/user/d/demattia/MuScleFit/Summer08/Zold/Filter_Z_46.root",
    "rfio:/castor/cern.ch/user/d/demattia/MuScleFit/Summer08/Zold/Filter_Z_47.root",
    "rfio:/castor/cern.ch/user/d/demattia/MuScleFit/Summer08/Zold/Filter_Z_48.root",
    "rfio:/castor/cern.ch/user/d/demattia/MuScleFit/Summer08/Zold/Filter_Z_49.root",
    "rfio:/castor/cern.ch/user/d/demattia/MuScleFit/Summer08/Zold/Filter_Z_5.root",
    "rfio:/castor/cern.ch/user/d/demattia/MuScleFit/Summer08/Zold/Filter_Z_50.root",
    "rfio:/castor/cern.ch/user/d/demattia/MuScleFit/Summer08/Zold/Filter_Z_6.root",
    "rfio:/castor/cern.ch/user/d/demattia/MuScleFit/Summer08/Zold/Filter_Z_7.root",
    "rfio:/castor/cern.ch/user/d/demattia/MuScleFit/Summer08/Zold/Filter_Z_8.root"
    )
                    )